<script lang="ts">
	import DeleteIcon from '$lib/DeleteIcon.svelte';
	import DownloadIcon from '$lib/DownloadIcon.svelte';
	import FolderIcon from '$lib/FolderIcon.svelte';
	import RenameIcon from '$lib/RenameIcon.svelte';
	import Name from './Name.svelte';

	// export let iconComponent: any;
	export let iconFunction: () => void;
	export let name: string;
	export let path: string;
	export let size: string;
	export let type: string;
</script>

<main class="flex flex-row hover:bg-slate-100 pl-4">
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
	<div class="pr-4">
		<RenameIcon />
	</div>
	<div class="pr-10">
		<DeleteIcon />
	</div>
</main>
