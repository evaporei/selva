#+build linux, darwin, freebsd, openbsd, netbsd, haiku
package selva

import "core:sys/posix"

foreign import libselva {
    "../../build/libselva.a",
}

Thread :: struct {
	handle: posix.pthread_t,
}

ThreadData :: struct {
	fn:  proc "c" (rawptr),
	arg: rawptr,
}

@(default_calling_convention="c", link_prefix="")
foreign libselva {
	thread_init   :: proc(thread: ^Thread, fn: proc "c" (rawptr), arg: rawptr) ---
	thread_join   :: proc(thread: ^Thread) ---
	thread_detach :: proc(thread: ^Thread) ---
}
