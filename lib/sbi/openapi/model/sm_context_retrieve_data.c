
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sm_context_retrieve_data.h"

OpenAPI_sm_context_retrieve_data_t *OpenAPI_sm_context_retrieve_data_create(
    OpenAPI_mme_capabilities_t *target_mme_cap,
    OpenAPI_sm_context_type_t *sm_context_type,
    OpenAPI_plmn_id_t *serving_network,
    OpenAPI_list_t *not_to_transfer_ebi_list
    )
{
    OpenAPI_sm_context_retrieve_data_t *sm_context_retrieve_data_local_var = OpenAPI_malloc(sizeof(OpenAPI_sm_context_retrieve_data_t));
    if (!sm_context_retrieve_data_local_var) {
        return NULL;
    }
    sm_context_retrieve_data_local_var->target_mme_cap = target_mme_cap;
    sm_context_retrieve_data_local_var->sm_context_type = sm_context_type;
    sm_context_retrieve_data_local_var->serving_network = serving_network;
    sm_context_retrieve_data_local_var->not_to_transfer_ebi_list = not_to_transfer_ebi_list;

    return sm_context_retrieve_data_local_var;
}

void OpenAPI_sm_context_retrieve_data_free(OpenAPI_sm_context_retrieve_data_t *sm_context_retrieve_data)
{
    if (NULL == sm_context_retrieve_data) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_mme_capabilities_free(sm_context_retrieve_data->target_mme_cap);
    OpenAPI_sm_context_type_free(sm_context_retrieve_data->sm_context_type);
    OpenAPI_plmn_id_free(sm_context_retrieve_data->serving_network);
    OpenAPI_list_for_each(sm_context_retrieve_data->not_to_transfer_ebi_list, node) {
        ogs_free(node->data);
    }
    OpenAPI_list_free(sm_context_retrieve_data->not_to_transfer_ebi_list);
    ogs_free(sm_context_retrieve_data);
}

cJSON *OpenAPI_sm_context_retrieve_data_convertToJSON(OpenAPI_sm_context_retrieve_data_t *sm_context_retrieve_data)
{
    cJSON *item = NULL;

    if (sm_context_retrieve_data == NULL) {
        ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [SmContextRetrieveData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (sm_context_retrieve_data->target_mme_cap) {
        cJSON *target_mme_cap_local_JSON = OpenAPI_mme_capabilities_convertToJSON(sm_context_retrieve_data->target_mme_cap);
        if (target_mme_cap_local_JSON == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [target_mme_cap]");
            goto end;
        }
        cJSON_AddItemToObject(item, "targetMmeCap", target_mme_cap_local_JSON);
        if (item->child == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [target_mme_cap]");
            goto end;
        }
    }

    if (sm_context_retrieve_data->sm_context_type) {
        cJSON *sm_context_type_local_JSON = OpenAPI_sm_context_type_convertToJSON(sm_context_retrieve_data->sm_context_type);
        if (sm_context_type_local_JSON == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [sm_context_type]");
            goto end;
        }
        cJSON_AddItemToObject(item, "smContextType", sm_context_type_local_JSON);
        if (item->child == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [sm_context_type]");
            goto end;
        }
    }

    if (sm_context_retrieve_data->serving_network) {
        cJSON *serving_network_local_JSON = OpenAPI_plmn_id_convertToJSON(sm_context_retrieve_data->serving_network);
        if (serving_network_local_JSON == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [serving_network]");
            goto end;
        }
        cJSON_AddItemToObject(item, "servingNetwork", serving_network_local_JSON);
        if (item->child == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [serving_network]");
            goto end;
        }
    }

    if (sm_context_retrieve_data->not_to_transfer_ebi_list) {
        cJSON *not_to_transfer_ebi_list = cJSON_AddArrayToObject(item, "notToTransferEbiList");
        if (not_to_transfer_ebi_list == NULL) {
            ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [not_to_transfer_ebi_list]");
            goto end;
        }

        OpenAPI_lnode_t *not_to_transfer_ebi_list_node;
        OpenAPI_list_for_each(sm_context_retrieve_data->not_to_transfer_ebi_list, not_to_transfer_ebi_list_node)  {
            if (cJSON_AddNumberToObject(not_to_transfer_ebi_list, "", *(double *)not_to_transfer_ebi_list_node->data) == NULL) {
                ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed [not_to_transfer_ebi_list]");
                goto end;
            }
        }
    }

end:
    return item;
}

OpenAPI_sm_context_retrieve_data_t *OpenAPI_sm_context_retrieve_data_parseFromJSON(cJSON *sm_context_retrieve_dataJSON)
{
    OpenAPI_sm_context_retrieve_data_t *sm_context_retrieve_data_local_var = NULL;
    cJSON *target_mme_cap = cJSON_GetObjectItemCaseSensitive(sm_context_retrieve_dataJSON, "targetMmeCap");

    OpenAPI_mme_capabilities_t *target_mme_cap_local_nonprim = NULL;
    if (target_mme_cap) {
        target_mme_cap_local_nonprim = OpenAPI_mme_capabilities_parseFromJSON(target_mme_cap);
    }

    cJSON *sm_context_type = cJSON_GetObjectItemCaseSensitive(sm_context_retrieve_dataJSON, "smContextType");

    OpenAPI_sm_context_type_t *sm_context_type_local_nonprim = NULL;
    if (sm_context_type) {
        sm_context_type_local_nonprim = OpenAPI_sm_context_type_parseFromJSON(sm_context_type);
    }

    cJSON *serving_network = cJSON_GetObjectItemCaseSensitive(sm_context_retrieve_dataJSON, "servingNetwork");

    OpenAPI_plmn_id_t *serving_network_local_nonprim = NULL;
    if (serving_network) {
        serving_network_local_nonprim = OpenAPI_plmn_id_parseFromJSON(serving_network);
    }

    cJSON *not_to_transfer_ebi_list = cJSON_GetObjectItemCaseSensitive(sm_context_retrieve_dataJSON, "notToTransferEbiList");

    OpenAPI_list_t *not_to_transfer_ebi_listList;
    if (not_to_transfer_ebi_list) {
        cJSON *not_to_transfer_ebi_list_local;
        if (!cJSON_IsArray(not_to_transfer_ebi_list)) {
            ogs_error("OpenAPI_sm_context_retrieve_data_parseFromJSON() failed [not_to_transfer_ebi_list]");
            goto end;
        }
        not_to_transfer_ebi_listList = OpenAPI_list_create();

        cJSON_ArrayForEach(not_to_transfer_ebi_list_local, not_to_transfer_ebi_list) {
            if (!cJSON_IsNumber(not_to_transfer_ebi_list_local)) {
                ogs_error("OpenAPI_sm_context_retrieve_data_parseFromJSON() failed [not_to_transfer_ebi_list]");
                goto end;
            }
            OpenAPI_list_add(not_to_transfer_ebi_listList, &not_to_transfer_ebi_list_local->valuedouble);
        }
    }

    sm_context_retrieve_data_local_var = OpenAPI_sm_context_retrieve_data_create (
        target_mme_cap ? target_mme_cap_local_nonprim : NULL,
        sm_context_type ? sm_context_type_local_nonprim : NULL,
        serving_network ? serving_network_local_nonprim : NULL,
        not_to_transfer_ebi_list ? not_to_transfer_ebi_listList : NULL
        );

    return sm_context_retrieve_data_local_var;
end:
    return NULL;
}

OpenAPI_sm_context_retrieve_data_t *OpenAPI_sm_context_retrieve_data_copy(OpenAPI_sm_context_retrieve_data_t *dst, OpenAPI_sm_context_retrieve_data_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_sm_context_retrieve_data_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_sm_context_retrieve_data_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_sm_context_retrieve_data_free(dst);
    dst = OpenAPI_sm_context_retrieve_data_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}
