<?php
/**
 * @file
 * expertnet_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function expertnet_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function expertnet_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function expertnet_core_node_info() {
  $items = array(
    'areas' => array(
      'name' => t('Areas'),
      'base' => 'node_content',
      'description' => t('Departments defined as Areas and Sub-Areas.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'projects' => array(
      'name' => t('Projects'),
      'base' => 'node_content',
      'description' => t('Projects can belong to multiple areas and have multiple collaboratos.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_search_api_index().
 */
function expertnet_core_default_search_api_index() {
  $items = array();
  $items['solr_user_index'] = entity_import('search_api_index', '{
    "name" : "Solr User Index",
    "machine_name" : "solr_user_index",
    "description" : null,
    "server" : "solr_server",
    "item_type" : "user",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "uid" : { "type" : "integer" },
        "name" : { "type" : "text" },
        "mail" : { "type" : "string" },
        "field_projects" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_interests" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_position" : { "type" : "text" },
        "search_api_language" : { "type" : "string" },
        "search_api_url" : { "type" : "uri" },
        "search_api_viewed" : { "type" : "text" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_role_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "roles" : [] }
        },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 1, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_url" : { "status" : 1, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "name" : true,
              "mail" : true,
              "field_projects" : true,
              "field_interests" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "name" : true,
              "mail" : true,
              "field_projects" : true,
              "field_interests" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 0,
          "weight" : "15",
          "settings" : { "fields" : { "name" : true } }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : { "name" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "name" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}
