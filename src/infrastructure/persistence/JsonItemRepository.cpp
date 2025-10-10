#include "JsonItemRepository.hpp"

#include "common/Definitions.hpp"
#include "common/ILogger.hpp"
#include "common/exceptions/RepositoryException.hpp"
#include "item/Item.hpp"
#include "stats/StatModifier.hpp"

#include "nlohmann/json.hpp"
#include "valijson/adapters/nlohmann_json_adapter.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/utils/nlohmann_json_utils.hpp"
#include "valijson/validation_results.hpp"
#include "valijson/validator.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace ugame::infrastructure
{

JsonItemRepository::JsonItemRepository(const std::filesystem::path& filepath, std::shared_ptr<core::ILogger> logger)
    : m_filepath{ filepath }
    , m_logger{ logger }
{}

const core::Item* JsonItemRepository::findById(ItemID id)
{
    try
    {
        checkCache();
    }
    catch(const core::RepositroyException& e)
    {
        throw;
    }

    if(auto it{ m_itemCache.find(id) }; it != m_itemCache.end())
        return &it->second;

    return nullptr;
}

std::vector<const core::Item*> JsonItemRepository::findAll()
{
    try
    {
        checkCache();
    }
    catch(const core::RepositroyException& e)
    {
        throw;
    }

    std::vector<const core::Item*> result;
    result.reserve(m_itemCache.size());

    for(auto& [_, item] : m_itemCache)
        result.push_back(&item);

    return result;
}

/// \brief Check if the cache is ready to be used
///
/// Check if the cache has already been loaded, if not load from file.
///
/// \throws \ref core::RepositroyException
void JsonItemRepository::checkCache()
{
    if(m_itemCache.empty())
    {
        try
        {
            loadItemsFromFile();
        }
        catch(const core::RepositroyException& e)
        {
            throw;
        }
    }
}

/// \brief Load all items from the file
///
/// \throws \ref core::RepositroyException when the file can't be opened or there is a issue with the parsing
void JsonItemRepository::loadItemsFromFile()
{
    std::ifstream in(m_filepath);
    if(!in.is_open())
    {
        m_logger->error("Failed to open item json file: {}", m_filepath.string());
        throw core::RepositroyException("Failed to open item file: " + m_filepath.string());
    }

    nlohmann::json j{};
    in >> j;

    if(!validateJson(j))
    {
        m_logger->warn("JSON did not validate against the expected scheme: {}", m_filepath.string());
        throw core::RepositroyException("Failed to validate against scheme: " + m_filepath.string());
    }

    m_logger->info("items in json: {}", j[ITEM_ARRAY_FIELD].size());

    for(auto& element : j[ITEM_ARRAY_FIELD])
    {
        core::StatModifier mods {
            .hp = element[STATS_FIELD][STATS_HP_FIELD].get<hp_t>(),
            .attack = element[STATS_FIELD][STATS_ATTACK_FIELD].get<attack_t>(),
            .defense = element[STATS_FIELD][STATS_DEFENSE_FIELD].get<defense_t>(),
            .speed = element[STATS_FIELD][STATS_SPEED_FIELD].get<speed_t>(),
            .luck = element[STATS_FIELD][STATS_LUCK_FIELD].get<luck_t>()
        };

        m_itemCache.emplace(
            element[ID_FIELD].get<ItemID>(), 
            core::Item{
                element[ID_FIELD].get<ItemID>(),
                element[NAME_FIELD].get<std::string>(),
                core::toItemType(element[TYPE_FIELD].get<std::string>()),
                mods
            }
        );

    }

    in.close();
}

/// \brief validate a json file against a schema
///
/// \param itemJson a nlohmann::json object that is being validated
///
/// \return *true* if validation was successfull, *false* if not
bool JsonItemRepository::validateJson(const nlohmann::json& itemJson) const
{
    std::filesystem::path schemaPath(std::string(RESOURCE_DIR) + SCHEMA_FILE_PATH);
    nlohmann::json schemaJson{};
    valijson::utils::loadDocument(schemaPath, schemaJson);

    valijson::Schema schema;
    valijson::SchemaParser parser;
    valijson::adapters::NlohmannJsonAdapter schemaAdapter(schemaJson);
    parser.populateSchema(schemaAdapter, schema);

    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter itemAdapter(itemJson);

    valijson::ValidationResults results;
    if(!validator.validate(schema, itemAdapter, &results))
    {
        m_logger->warn("JSON validation failed");

        std::stringstream errorMessage{};
        for(const auto& r : results)
            errorMessage << "\t- " << r.description;

        m_logger->warn(errorMessage.str());
        return false;
    }

    m_logger->info("JSON validation successfull");
    return true;
}

} // !ugame::infrastructure
