<script lang="ts">
	import { renameFile } from '$lib/Functions';
	export let name: string;
	export let path: string;
	let isEditable = false;
	let newName: string;
	let inputRef: HTMLInputElement;
	$: type = name.slice(name.lastIndexOf('.') + 1);

	function saveChanges() {
		if (newName != name) {
			renameFile(path + '/' + name, path + '/' + newName);
			name = newName;
		}
		isEditable = false;
	}

	function discardChanges() {
		isEditable = false;
	}

	function startEditing() {
		newName = name;
		isEditable = true;
		// Set focus to the input field when starting editing
		requestAnimationFrame(() => {
			inputRef.focus();
			inputRef.setSelectionRange(0, name.lastIndexOf('.'));
		});
	}

	function handleKeyDown(event: KeyboardEvent) {
		// Handle Enter key to save the changes and Escape key to discard the changes
		if (event.key === 'Enter') {
			saveChanges();
		} else if (event.key === 'Escape') {
			discardChanges();
		}
	}
</script>

<div on:dblclick={startEditing} aria-hidden="true">
	{#if isEditable}
		<input
			type="text"
			bind:value={newName}
			bind:this={inputRef}
			on:keydown={handleKeyDown}
			on:blur={saveChanges}
			class="bg-transparent border-b focus:outline-none focus:bg-slate-100"
		/>
	{:else}
		{name}
	{/if}
</div>
