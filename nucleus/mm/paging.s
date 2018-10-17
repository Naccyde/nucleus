global enable_paging

; enable_paging - Enable paging system
; stack: [esp + 4] Page directory address
;	 [esp    ] Return address
enable_paging:
	; Load page directory
	mov eax, [esp + 4]
	mov cr3, eax

	; Disable 4Mib pages
	mov ecx, cr4
	and ecx, 0xFFFFFFEF
	mov cr4, ecx

	; Enable paging
	mov eax, cr0
	or eax, 0x80000001	; Set PE flag when setting PG flag
	mov cr0, eax
	ret

clean_tlb:
	invlpg [0]
	invlpg [768]
	ret