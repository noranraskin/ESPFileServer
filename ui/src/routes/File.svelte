<script lang="ts">
	import Item from './Item.svelte';
	import { downloadFile } from '$lib/Functions';

	export let name: string;
	export let path: string;
	export let size: string;
</script>

<Item
	{name}
	{path}
	{size}
	type={'file'}
	iconFunction={() => {
		downloadFile(path, name);
	}}
/>
