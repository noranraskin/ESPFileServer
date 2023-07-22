<script lang="ts">
	export let name: String;
	export let size: String;
	$: type = name.slice(name.lastIndexOf('.') + 1);
</script>

<main class="flex flex-row">
	<div class="grow">
		{name}
	</div>
	<div class="pr-20">
		{size}
	</div>
</main>
