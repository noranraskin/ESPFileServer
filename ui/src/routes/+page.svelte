<script lang="ts">
	import { onMount } from 'svelte';
	import {
		isMoving,
		loadListOfFiles,
		updateFSInfo,
		itemUnderCursor,
		renameFile
	} from '$lib/Functions';
	import Folder from './Folder.svelte';
	import FolderIcon from '$lib/FolderIcon.svelte';
	import AvailableSpaceBar from './AvailableSpaceBar.svelte';
	var currentYear = new Date().getFullYear();
	import { FS } from '$lib/Functions';
	import {
		isDragging,
		draggedItem,
		dragOffsetX,
		dragOffsetY,
		draggedItemName,
		draggedItemPath
	} from '$lib/Functions';

	onMount(() => {
		try {
			loadListOfFiles();
		} catch (error) {
			console.log(error);
		}
	});

	function handleMouseMove(event: MouseEvent) {
		if ($isDragging) {
			const deltaX = event.clientX - $dragOffsetX;
			const deltaY = event.clientY - $dragOffsetY;
			$isMoving = true;
			if ($draggedItem) {
				const $draggedItemTyped = $draggedItem as HTMLElement;
				$draggedItemTyped.style.transform = 'translate(0, 0)';
				$draggedItemTyped.style.transform = `translate(${deltaX}px, ${deltaY}px)`;
				$draggedItemTyped.style.pointerEvents = 'none';
				$draggedItemTyped.style.opacity = '0.5';
			}
		}
	}

	function handleMouseUp(event: MouseEvent) {
		if ($isDragging) {
			if ($draggedItem) {
				const $draggedItemTyped = $draggedItem as HTMLElement;
				$draggedItemTyped.style.transform = 'translate(0, 0)';
				$draggedItemTyped.style.pointerEvents = 'auto';
				$draggedItemTyped.style.opacity = '1';
			}
			let newPath = $itemUnderCursor.join('/') + '/' + $draggedItemName;
			let oldPath: string;
			if ($draggedItemPath == '/') {
				oldPath = '/' + $draggedItemName;
			} else {
				oldPath = $draggedItemPath + '/' + $draggedItemName;
			}
			if (newPath != oldPath) {
				renameFile(oldPath, newPath);
			}
			$isDragging = false;
			$draggedItem = null;
			$draggedItemName = '';
			$draggedItemPath = '';
			$isMoving = false;
		}
	}
</script>

<main class="flex-col" on:mousemove={handleMouseMove} on:mouseup={handleMouseUp} aria-hidden="true">
	<div class="flex justify-center p-5">
		<div class="flex flex-row justify-self-center">
			<FolderIcon width={100} />
			<h1 class="font-bold self-center text-4xl px-8">ESPFileServer</h1>
		</div>
	</div>

	<div class="flex flex-col">
		<div class="w-5/6 m-auto">
			<div class="flex flex-col py-4">
				<AvailableSpaceBar />
			</div>
			<div class="flex flex-col border-r">
				<Folder name="" size="" files={$FS} path="" />
			</div>
		</div>
		<div class="flex grow" />
		<div class="flex flex-col p-3 items-center pt-10">
			<div>
				Icons by <a href="https://iconoir.com/">Iconoir</a>.
			</div>
			<div>
				© {currentYear} Noran Raskin.
			</div>
		</div>
	</div>
</main>
