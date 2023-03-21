/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright Authors of Cilium */

#ifndef __BPF_ACCESS_H_
#define __BPF_ACCESS_H_

#include "compiler.h"

#if !defined(__non_bpf_context) && defined(__bpf__)
/* 
 OPENED COMMENT BEGIN 
{
  "capabilities": [],
  "helperCallParams": {},
  "startLine": 10,
  "endLine": 33,
  "File": "/home/sayandes/ebpf-projects-annotations/examples/cilium/include/bpf/access.h",
  "funcName": "map_array_get_32",
  "developer_inline_comments": [
    {
      "start_line": 1,
      "end_line": 1,
      "text": "/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */"
    },
    {
      "start_line": 2,
      "end_line": 2,
      "text": "/* Copyright Authors of Cilium */"
    },
    {
      "start_line": 19,
      "end_line": 23,
      "text": "/* LLVM tends to optimize code away that is needed for the verifier to\n\t * understand dynamic map access. Input constraint is that index < limit\n\t * for this util function, so we never fail here, and returned datum is\n\t * always valid.\n\t */"
    },
    {
      "start_line": 30,
      "end_line": 30,
      "text": "/* no clobbers */"
    }
  ],
  "updateMaps": [],
  "readMaps": [],
  "input": [
    "const __u32 *array",
    " __u32 index",
    " const __u32 limit"
  ],
  "output": "static__always_inline__maybe_unused__u32",
  "helper": [],
  "compatibleHookpoints": [
    "lwt_xmit",
    "lwt_out",
    "lwt_seg6local",
    "sk_skb",
    "sched_cls",
    "socket_filter",
    "sk_reuseport",
    "sk_msg",
    "kprobe",
    "xdp",
    "cgroup_skb",
    "raw_tracepoint_writable",
    "lwt_in",
    "perf_event",
    "cgroup_sock",
    "cgroup_sock_addr",
    "raw_tracepoint",
    "flow_dissector",
    "cgroup_sysctl",
    "sock_ops",
    "tracepoint",
    "sched_act",
    "cgroup_device"
  ],
  "source": [
    "static __always_inline __maybe_unused __u32 map_array_get_32 (const __u32 *array, __u32 index, const __u32 limit)\n",
    "{\n",
    "    __u32 datum = 0;\n",
    "    if (__builtin_constant_p (index) || !__builtin_constant_p (limit))\n",
    "        __throw_build_bug ();\n",
    "    asm volatile (\"%[index] <<= 2\\n\\t\"\n",
    "        \"if %[index] > %[limit] goto +1\\n\\t\"\n",
    "        \"%[array] += %[index]\\n\\t\"\n",
    "        \"%[datum] = *(u32 *)(%[array] + 0)\\n\\t\"\n",
    "        : [datum] \"=r\"\n",
    "        (datum) : [limit] \"i\"\n",
    "        (limit), [array] \"r\"\n",
    "        (array), [index] \"r\"\n",
    "        (index) :);\n",
    "    return datum;\n",
    "}\n"
  ],
  "called_function_list": [
    "__builtin_constant_p",
    "__throw_build_bug"
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
static __always_inline __maybe_unused __u32
map_array_get_32(const __u32 *array, __u32 index, const __u32 limit)
{
	__u32 datum = 0;

	if (__builtin_constant_p(index) ||
	    !__builtin_constant_p(limit))
		__throw_build_bug();

	/* LLVM tends to optimize code away that is needed for the verifier to
	 * understand dynamic map access. Input constraint is that index < limit
	 * for this util function, so we never fail here, and returned datum is
	 * always valid.
	 */
	asm volatile("%[index] <<= 2\n\t"
		     "if %[index] > %[limit] goto +1\n\t"
		     "%[array] += %[index]\n\t"
		     "%[datum] = *(u32 *)(%[array] + 0)\n\t"
		     : [datum]"=r"(datum)
		     : [limit]"i"(limit), [array]"r"(array), [index]"r"(index)
		     : /* no clobbers */ );

	return datum;
}
#else
# define map_array_get_32(array, index, limit)	__throw_build_bug()
#endif /* !__non_bpf_context && __bpf__ */
#endif /* __BPF_ACCESS_H_ */