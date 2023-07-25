<script lang="ts">
	import File from './File.svelte';
	import Item from './Item.svelte';
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

<main class="font-bold flex-col flex hover:bg-slate-200">
	{#if name != ''}
		<Item {name} {path} {size} type={'folder'} iconFunction={toggle} />
	{/if}
</main>
{#if expanded}
	<ul class="right-4 border border-slate-300">
		{#each files as file}
			<li class="py-1 pl-4">
				{#if file.files}
					<div class="">
						<svelte:self {...file} path={newPath} />
					</div>
				{:else}
					<File {...file} path={newPath} />
				{/if}
			</li>
		{/each}
	</ul>
{/if}
