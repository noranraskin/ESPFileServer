<script lang="ts">
	import File from './File.svelte';

	export let expanded = true;
	export let name: String;
	export let size: String;
	export let files: Array<any>;

	function toggle() {
		expanded = !expanded;
	}
</script>

<main class="font-bold flex-row flex">
	<button class="bg-slate-200 px-1" on:click={toggle}>{name}</button>
	<div class="grow" />
	<div class="pr-20">{size}</div>
</main>
{#if expanded}
	<ul class="pl-4 right-4 border border-slate-300">
		{#each files as file}
			<li class="py-1">
				{#if file.files}
					<svelte:self {...file} />
				{:else}
					<File {...file} />
				{/if}
			</li>
		{/each}
	</ul>
{/if}
