// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef struct bpf_map {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
} bpf_map_def_t;
#define BPF_MAP_TYPE_ARRAY 2

__attribute__((section("maps"), used))
bpf_map_def_t map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(uint32_t),
     .value_size = sizeof(uint32_t),
     .max_entries = 1};

struct bpf_sock_ops;

static int (*bpf_sock_map_update)(struct bpf_sock_ops *skops, struct bpf_map *map, void *key, uint64_t flags) = (void*) 53;

__attribute__((section("xdp"), used))
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [
    {
      "capability": "map_update",
      "map_update": [
        {
          "Project": "libbpf",
          "Return Type": "int",
          "Description": "Add an entry to , or update a <[ map ]>(IP: 1) referencing sockets. The <[ skops ]>(IP: 0) is used as a new value for the entry associated to key. <[ flags ]>(IP: 3) is one of: BPF_NOEXIST The entry for <[ key ]>(IP: 2) must not exist in the map. BPF_EXIST The entry for <[ key ]>(IP: 2) must already exist in the map. BPF_ANY No condition on the existence of the entry for key. If the <[ map ]>(IP: 1) has eBPF programs (parser and verdict) , those will be inherited by the socket being added. If the socket is already attached to eBPF programs , this results in an error. ",
          "Return": " 0 on success, or a negative error in case of failure.",
          "Function Name": "bpf_sock_map_update",
          "Input Params": [
            "{Type: struct bpf_sock_ops ,Var: *skops}",
            "{Type:  struct bpf_map ,Var: *map}",
            "{Type:  void ,Var: *key}",
            "{Type:  u64 ,Var: flags}"
          ],
          "compatible_hookpoints": [
            "sock_ops"
          ],
          "capabilities": [
            "map_update"
          ]
        }
      ]
    }
  ],
  "helperCallParams": {},
  "startLine": 29,
  "endLine": 37,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/vpf-ebpf-src/wronghelper.c",
  "funcName": "func",
  "developer_inline_comments": [
    {
      "start_line": 1,
      "end_line": 1,
      "text": "// Copyright (c) Prevail Verifier contributors."
    },
    {
      "start_line": 2,
      "end_line": 2,
      "text": "// SPDX-License-Identifier: MIT"
    },
    {
      "start_line": 33,
      "end_line": 33,
      "text": "// The following should fail because the ctx doesn't match, and in particular"
    },
    {
      "start_line": 34,
      "end_line": 34,
      "text": "// the memory pointed to by ctx might be smaller than the memory read by the helper."
    }
  ],
  "updateMaps": [
    " ctx"
  ],
  "readMaps": [],
  "input": [
    "void *ctx"
  ],
  "output": "int",
  "helper": [
    "bpf_sock_map_update"
  ],
  "compatibleHookpoints": [
    "sock_ops"
  ],
  "source": [
    "int func (void *ctx)\n",
    "{\n",
    "    uint32_t key = 1;\n",
    "    int result = bpf_sock_map_update (ctx, & map, & key, 0);\n",
    "    return result;\n",
    "}\n"
  ],
  "called_function_list": [
    "ebpf_get_current_comm",
    "ebpf_map_update_elem"
  ],
  "call_depth": -1,
  "humanFuncDescription": [
    {}
  ],
  "AI_func_description": [
    {
      "description": "",
      "author": "",
      "authorEmail": "",
      "date": "",
      "invocationParameters": ""
    }
  ]
} 
 OPENED COMMENT END 
 */ 
int func(void* ctx)
{
    uint32_t key = 1;

    // The following should fail because the ctx doesn't match, and in particular
    // the memory pointed to by ctx might be smaller than the memory read by the helper.
    int result = bpf_sock_map_update(ctx, &map, &key, 0);
    return result;
}