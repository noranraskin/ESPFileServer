<script lang="ts">
	import DeleteIcon from '$lib/DeleteIcon.svelte';
	import DownloadIcon from '$lib/DownloadIcon.svelte';
	import RenameIcon from '$lib/RenameIcon.svelte';
	import { downloadFile } from '$lib/Functions';

	export let name: string;
	export let path: string;
	export let size: string;
	$: type = name.slice(name.lastIndexOf('.') + 1);
</script>

<main class="flex flex-row">
	<div class="grow">
		{name}
	</div>
	<div class="pr-4">
		{size}
	</div>
	<div class="pr-4">
		<button on:click={() => downloadFile(path, name)}>
			<DownloadIcon />
		</button>
	</div>
	<div class="pr-4">
		<RenameIcon />
	</div>
	<div class="pr-10">
		<DeleteIcon />
	</div>
</main>
