<script lang="ts">
	import DeleteIcon from '$lib/DeleteIcon.svelte';
	import DownloadIcon from '$lib/DownloadIcon.svelte';
	import RenameIcon from '$lib/RenameIcon.svelte';
	import { downloadFile } from '$lib/Functions';
	import Name from './Name.svelte';

	export let name: string;
	export let path: string;
	export let size: string;
	$: type = name.slice(name.lastIndexOf('.') + 1);
</script>

<main class="flex flex-row hover:bg-slate-100 pl-4">
	<div class="grow">
		<Name {name} {path} />
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
