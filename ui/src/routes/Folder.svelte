<script lang="ts">
	import File from './File.svelte';
	import DeleteIcon from '$lib/DeleteIcon.svelte';
	import DownloadIcon from '$lib/DownloadIcon.svelte';
	import RenameIcon from '$lib/RenameIcon.svelte';
	// import { downloadFolder } from '$lib/Functions';

	export let expanded = true;
	export let name: string;
	export let size: string;
	export let files: Array<any>;
	export let path: string;
	let newPath = (path == '/' ? path : path + '/') + name;

	function toggle() {
		expanded = !expanded;
	}
</script>

<main class="font-bold flex-row flex">
	{#if name != ''}
		<button class="bg-slate-200 px-1" on:click={toggle}>{name}</button>
		<div class="grow" />
		<div class="pr-4">{size}</div>
		<div class="pr-4">
			<button
				on:click={() => {
					// downloadFolder({ name: name, files: files }, path);
				}}
			>
				<DownloadIcon stroke_width={2.5} />
			</button>
		</div>
		<div class="pr-4">
			<RenameIcon stroke_width={2.5} />
		</div>
		<div class="pr-10">
			<DeleteIcon stroke_width={2.5} />
		</div>
	{/if}
</main>
{#if expanded}
	<ul class="pl-4 right-4 border border-slate-300">
		{#each files as file}
			<li class="py-1">
				{#if file.files}
					<svelte:self {...file} path={newPath} />
				{:else}
					<File {...file} path={newPath} />
				{/if}
			</li>
		{/each}
	</ul>
{/if}
