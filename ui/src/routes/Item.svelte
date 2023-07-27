<script lang="ts">
	import DeleteIcon from '$lib/DeleteIcon.svelte';
	import DownloadIcon from '$lib/DownloadIcon.svelte';
	import FolderIcon from '$lib/FolderIcon.svelte';
	import Name from './Name.svelte';
	import {
		isDragging,
		draggedItem,
		dragOffsetX,
		dragOffsetY,
		draggedItemName,
		draggedItemPath
	} from '$lib/Functions';

	// export let iconComponent: any;
	export let iconFunction: () => void;
	export let name: string;
	export let path: string;
	export let size: string;
	export let type: string;

	let mainElement: any;

	function handleMouseDown(event: MouseEvent) {
		$isDragging = true;
		$dragOffsetX = event.clientX;
		$dragOffsetY = event.clientY;
		$draggedItem = mainElement;
		$draggedItemPath = path;
		$draggedItemName = name;
	}
</script>

<main
	class="flex flex-row hover:bg-slate-100 pl-4"
	bind:this={mainElement}
	on:mousedown={handleMouseDown}
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
	<div class="pr-4">
		{size}
	</div>
	<div class="pr-10">
		<DeleteIcon />
	</div>
</main>
