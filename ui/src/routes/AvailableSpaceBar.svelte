<script lang="ts">
	import { totalBytes } from '$lib/Functions';
	import { usedBytes } from '$lib/Functions';
</script>

<main class="flex">
	<div class="flex flex-row grow h-6 border rounded">
		<div
			class="flex h-full min-w-0 bg-gray-700 border rounded justify-center"
			style="width: {($usedBytes / $totalBytes) * 100}%;"
		>
			<p class="flex text-xs text-white self-center truncate overflow-hidden">
				{(($usedBytes / $totalBytes) * 100).toFixed(2)} %
			</p>
		</div>
		<div class="flex grow self-center min-w-0 justify-end" />
	</div>
	<p class="flex self-center text-xs px-2">
		{$usedBytes} / {$totalBytes} bytes used
	</p>
</main>
