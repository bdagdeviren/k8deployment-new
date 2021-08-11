package main

import "C"
import (
	"encoding/json"
    "github.com/johandry/klient"
    "gopkg.in/yaml.v2"
    "io/ioutil"
    metav1 "k8s.io/apimachinery/pkg/apis/meta/v1"
    "k8s.io/client-go/kubernetes"
    "k8s.io/client-go/rest"
    "path/filepath"
    "strings"
)

type YamlFile struct {
	WaitTime int64 `yaml:"waitTime"`
	Deployment []Deployment `yaml:"deployment"`
}

type Deployment struct {
	Name string `yaml:"name"`
	Path string `yaml:"path"`
	Wait Wait `yaml:"wait"`
}

type Wait struct {
	Name string `yaml:"name"`
	Namespace string `yaml:"namespace"`
}

func Client() (*kubernetes.Clientset,error) {
	config, err := rest.InClusterConfig()
	if err != nil {
		return nil,err
	}
	// creates the clientset
	clientset, err := kubernetes.NewForConfig(config)
	if err != nil {
		return nil,err
	}

	return clientset,nil
}

//export create_yaml
func create_yaml(subpath *C.char, path *C.char) (rc int,result *C.char,errStr *C.char) {
	file, err := ioutil.ReadFile(filepath.Join(C.GoString(subpath),C.GoString(path)))
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	c := klient.New("", "")
	err = c.Create(file)
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	resultFile := "Successfully create "+C.GoString(path)+" file!"
	return 0,C.CString(resultFile),nil
}

//export update_yaml
func update_yaml(subpath *C.char, path *C.char) (rc int,result *C.char,errStr *C.char) {
	file, err := ioutil.ReadFile(filepath.Join(C.GoString(subpath),C.GoString(path)))
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	c := klient.New("", "")
	err = c.Replace(file)
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	resultFile := "Successfully update "+C.GoString(path)+" file!"
	return 0,C.CString(resultFile),nil
}

//export delete_yaml
func delete_yaml(subpath *C.char, path *C.char) (rc int,result *C.char,errStr *C.char) {
	file, err := ioutil.ReadFile(filepath.Join(C.GoString(subpath),C.GoString(path)))
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	c := klient.New("", "")
	err = c.Delete(file)
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	resultFile := "Successfully delete "+C.GoString(path)+" file!"
	return 0,C.CString(resultFile),nil
}

//export apply_yaml
func apply_yaml(subpath *C.char, path *C.char) (rc int,result *C.char,errStr *C.char) {
	file, err := ioutil.ReadFile(filepath.Join(C.GoString(subpath),C.GoString(path)))
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	c := klient.New("", "")
	err = c.Apply(file)
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	resultFile := "Successfully apply "+C.GoString(path)+" file!"
	return 0,C.CString(resultFile),nil
}

//export check_pod_status
func check_pod_status(namespace *C.char,podName *C.char) (rc int,result *C.char,errStr *C.char) {
	clientset,err := Client()
	if err != nil {
    	return -1, nil, C.CString(err.Error())
    }

	isDeployed := false

	pods, err := clientset.CoreV1().Pods(C.GoString(namespace)).List(metav1.ListOptions{})
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	for _, element := range pods.Items {
		if strings.Contains(element.Name, C.GoString(podName)) {
			if element.Status.Phase == "Running" {
				isDeployed = true
			} else {
				isDeployed = false
			}
		}
	}

	resultGo := ""
	if isDeployed != false {
		resultGo = "Deployment Successfully - Name: "+C.GoString(podName)+", Namespace: "+C.GoString(namespace)
		return 0, C.CString(resultGo), nil
	} else {
		resultGo = "Waiting Pod Deployment - Name: "+C.GoString(podName)+", Namespace: "+ C.GoString(namespace)
		return -1, C.CString(resultGo), nil
	}
}

//export yaml_to_json
func yaml_to_json(path *C.char,fileC *C.char) (rc int,result *C.char,errStr *C.char) {
	yamlFile := YamlFile{}


	file, err := ioutil.ReadFile(filepath.Join(C.GoString(path),C.GoString(fileC)))
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	err = yaml.Unmarshal(file, &yamlFile)
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	b, err := json.Marshal(yamlFile)
	if err != nil {
		return -1, nil, C.CString(err.Error())
	}

	return 0, C.CString(string(b)), nil
}

func main() {
	//for _,element := range yamlFile.Deployment {
	//	if element.Wait.Name != "" && element.Wait.Namespace != "" {
	//		if CheckPodsStatus(element.Wait.Namespace,element.Wait.Name,yamlFile.WaitTime) {
	//			fmt.Printf("Applying Yaml - Name: %s, Path: %s \n",element.Name,element.Path)
	//		}
	//	}else {
	//		fmt.Printf("Applying Yaml - Name: %s, Path: %s \n",element.Name,element.Path)
	//	}
	//}
}