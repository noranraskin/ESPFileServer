<script lang="ts">
	import DeleteIcon from '$lib/DeleteIcon.svelte';
	import DownloadIcon from '$lib/DownloadIcon.svelte';
	import FolderIcon from '$lib/FolderIcon.svelte';
	import Name from './Name.svelte';

	// export let iconComponent: any;
	export let iconFunction: () => void;
	export let name: string;
	export let path: string;
	export let size: string;
	export let type: string;

	let isDragging = false;
	let showButtons = true;
	let dragOffsetX = 0;
	let dragOffsetY = 0;
	let mainElement: any;

	function handleMouseDown(event: MouseEvent) {
		isDragging = true;
		dragOffsetX = event.clientX;
		dragOffsetY = event.clientY;
	}

	function handleMouseMove(event: MouseEvent) {
		if (isDragging) {
			const deltaX = event.clientX - dragOffsetX;
			const deltaY = event.clientY - dragOffsetY;
			mainElement.style.transform = `translate(${deltaX}px, ${deltaY}px)`;
			mainElement.style.opacity = '0.5';
			showButtons = false;
		}
	}

	function handleMouseUp(event: MouseEvent) {
		if (isDragging) {
			mainElement.style.transform = 'translate(0, 0)';
			isDragging = false;
			mainElement.style.opacity = '1';
			showButtons = true;
		}
	}
</script>

<main
	class="flex flex-row hover:bg-slate-100 pl-4"
	bind:this={mainElement}
	on:mousedown={handleMouseDown}
	on:mousemove={handleMouseMove}
	on:mouseup={handleMouseUp}
	aria-hidden="true"
>
	<div class="flex justify-center pr-2">
		<button on:click={iconFunction}>
			{#if type == 'file'}
				<DownloadIcon />
			{:else}
				<FolderIcon />
			{/if}
		</button>
	</div>
	<div class="grow">
		<Name {name} {path} />
	</div>
	{#if showButtons}
		<div class="pr-4">
			{size}
		</div>
		<div class="pr-10">
			<DeleteIcon />
		</div>
	{:else}
		<!-- Invisible element filling the screen for capturing mouseMove and mouseUp events -->
		<div class="absolute -z-20 -translate-x-60 -translate-y-60 inset-0 h-full p-80 opacity-0" />
	{/if}
</main>
