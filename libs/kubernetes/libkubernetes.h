/* Code generated by cmd/cgo; DO NOT EDIT. */

/* package command-line-arguments */


#line 1 "cgo-builtin-export-prolog"

#include <stddef.h> /* for ptrdiff_t below */

#ifndef GO_CGO_EXPORT_PROLOGUE_H
#define GO_CGO_EXPORT_PROLOGUE_H

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

#endif

/* Start of preamble from import "C" comments.  */




/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef __SIZE_TYPE__ GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif


/* Return type for create_yaml */
struct create_yaml_return {
	GoInt r0; /* rc */
	char* r1; /* result */
	char* r2; /* errStr */
};
extern __declspec(dllexport) struct create_yaml_return create_yaml(char* path);

/* Return type for update_yaml */
struct update_yaml_return {
	GoInt r0; /* rc */
	char* r1; /* result */
	char* r2; /* errStr */
};
extern __declspec(dllexport) struct update_yaml_return update_yaml(char* path);

/* Return type for delete_yaml */
struct delete_yaml_return {
	GoInt r0; /* rc */
	char* r1; /* result */
	char* r2; /* errStr */
};
extern __declspec(dllexport) struct delete_yaml_return delete_yaml(char* path);

/* Return type for apply_yaml */
struct apply_yaml_return {
	GoInt r0; /* rc */
	char* r1; /* result */
	char* r2; /* errStr */
};
extern __declspec(dllexport) struct apply_yaml_return apply_yaml(char* path);

/* Return type for check_pod_status */
struct check_pod_status_return {
	GoInt r0; /* rc */
	char* r1; /* result */
	char* r2; /* errStr */
};
extern __declspec(dllexport) struct check_pod_status_return check_pod_status(char* namespace, char* podName);

/* Return type for yaml_to_json */
struct yaml_to_json_return {
	GoInt r0; /* rc */
	char* r1; /* result */
	char* r2; /* errStr */
};
extern __declspec(dllexport) struct yaml_to_json_return yaml_to_json(char* path, char* fileC);

#ifdef __cplusplus
}
#endif
