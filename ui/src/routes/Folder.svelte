<script lang="ts">
	import File from './File.svelte';
	import Item from './Item.svelte';
	import { itemUnderCursor, draggedItemName, draggedItemPath, isMoving } from '$lib/Functions';
	// import { downloadFolder } from '$lib/Functions';

	export let expanded = true;
	export let name: string;
	export let size: string;
	export let files: Array<any>;
	export let path: string;

	$: isHovering = $itemUnderCursor[$itemUnderCursor.length - 1] == name && $isMoving;
	$: hideChildren = $draggedItemName == name && $draggedItemPath == path && name != '' && $isMoving;
	let newPath = (path == '/' ? path : path + '/') + name;

	function toggle() {
		expanded = !expanded;
	}
</script>

<main
	on:mouseenter={() => {
		$itemUnderCursor = [...$itemUnderCursor, name];
	}}
	on:mouseleave={() => {
		$itemUnderCursor.splice($itemUnderCursor.indexOf(name), 1);
		$itemUnderCursor = [...$itemUnderCursor];
	}}
	class={isHovering ? 'bg-gray-100' : ''}
>
	<div class="font-bold flex-col flex hover:bg-slate-200">
		{#if name != ''}
			<Item {name} {path} {size} type={'folder'} iconFunction={toggle} />
		{/if}
	</div>
	{#if expanded && !hideChildren}
		<ul class="right-4 border-y border-l rounded-sm">
			{#each files as file}
				<li class="py-1 pl-4">
					{#if file.files}
						<div class="">
							<svelte:self {...file} path={newPath} />
						</div>
					{:else}
						<div class="">
							<File {...file} path={newPath} />
						</div>
					{/if}
				</li>
			{/each}
		</ul>
	{/if}
</main>
