#include <string.h>
#include <stdio.h>
#include "cjson/cJSON.h"
#include "log.h"
#include "libs/kubernetes/libkubernetes.h"

void deploy_yaml(const char *json_string){
    cJSON * root = cJSON_Parse(json_string);

    int waitTime = 0;
    if(cJSON_HasObjectItem(root,"WaitTime")) {
        cJSON *waitTime_item = cJSON_GetObjectItem(root, "WaitTime");
        if (cJSON_IsNumber(waitTime_item)) {
            waitTime = (int) waitTime_item->valuedouble;
        }
    }

    log_info("Waiting Time - %d",waitTime);

    if(cJSON_HasObjectItem(root,"Deployment")) {
        cJSON *deployment_item = cJSON_GetObjectItem(root, "Deployment");
        for (int i = 0; i < cJSON_GetArraySize(deployment_item); i++) {
            cJSON *subitem = cJSON_GetArrayItem(deployment_item, i);

            if(cJSON_HasObjectItem(subitem,"Name") && cJSON_HasObjectItem(subitem,"Path")) {

                cJSON *deployment_name = cJSON_GetObjectItem(subitem, "Name");
                cJSON *deployment_path = cJSON_GetObjectItem(subitem, "Path");

                if(cJSON_HasObjectItem(subitem,"Wait")) {

                    cJSON *deployment_wait = cJSON_GetObjectItem(subitem, "Wait");

                    if(cJSON_HasObjectItem(deployment_wait,"Name") && cJSON_HasObjectItem(deployment_wait,"Namespace")) {

                        cJSON *deployment_wait_name = cJSON_GetObjectItem(deployment_wait, "Name");
                        cJSON *deployment_wait_namespace = cJSON_GetObjectItem(deployment_wait, "Namespace");

                        if (strlen(deployment_wait_name->valuestring) != 0 && strlen(deployment_wait_namespace->valuestring) != 0) {
                            log_info("Checking Pod Deployment - Name: %s, Namespace: %s",deployment_wait_name->valuestring,deployment_wait_namespace->valuestring);
                            while(1){
                                struct check_pod_status_return check_pod_status_return;
                                check_pod_status_return = check_pod_status(deployment_wait_namespace->valuestring,deployment_wait_name->valuestring);
                                if (check_pod_status_return.r0 != 0) {
                                    log_error(check_pod_status_return.r1);
                                } else {
                                    log_info(check_pod_status_return.r1);
                                    log_info("Applying Yaml - Name: %s, Path: %s",deployment_name->valuestring,deployment_path->valuestring);
                                    struct apply_yaml_return applyYamlReturn;
                                    applyYamlReturn = apply_yaml("deployment",deployment_path->valuestring);
                                    if (applyYamlReturn.r0 != 0) {
                                        log_error(applyYamlReturn.r2);
                                    } else {
                                        log_info(applyYamlReturn.r1);
                                    }
                                    break;
                                }
                            }
                        }else{
                            log_info("Applying Yaml - Name: %s, Path: %s",deployment_name->valuestring,deployment_path->valuestring);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    struct yaml_to_json_return yaml_to_json_return;
    yaml_to_json_return = yaml_to_json("deployment","deployment.yaml");
    if (yaml_to_json_return.r0 != 0) {
        log_error(yaml_to_json_return.r2);
    } else {
        deploy_yaml(yaml_to_json_return.r1);
    }
}
