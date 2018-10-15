global load_page_directory
global enable_paging

; load_page_directory - Load the page directory
; stack: [esp + 4] Page directory address
;	 [esp    ] Return address
load_page_directory:
	mov eax, [esp + 4]
	mov cr3, eax
	ret

; enable_paging - Enable paging feature
; stack: [esp    ] Return address
enable_paging:
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	ret
