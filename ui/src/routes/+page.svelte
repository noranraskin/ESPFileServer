<script lang="ts">
	import Folder from './Folder.svelte';
	import FolderIcon from './FolderIcon.svelte';
	var currentYear = new Date().getFullYear();

	let root = [
		{
			name: 'excel',
			size: '5 KB',
			files: [
				{
					name: 'sheet.xlsx',
					size: '5 KB'
				}
			]
		},
		{
			name: 'other',
			size: '3 MB',
			files: [
				{
					name: 'logs',
					size: '1.3 MB',
					files: [
						{
							name: 'errors.log',
							size: '31 KB'
						},
						{
							name: 'latest.log',
							size: '1.2 MB'
						}
					]
				},
				{
					name: 'pics',
					size: '1 MB',
					files: [
						{ name: 'img.gif', size: '32 KB' },
						{ name: 'logo.png', size: '875 KB' }
					]
				},
				{ name: 'text.txt', size: '2 KB' },
				{ name: 'archive.tar.gz', size: '7 KB' },
				{ name: 'script.pdf', size: '1.3 MB' }
			]
		},
		{ name: 'TODO.md', size: '6 KB' }
	];
</script>

<div class="flex justify-center p-5">
	<div class="flex flex-row justify-self-center">
		<FolderIcon />
		<h1 class="font-bold self-center text-4xl px-8">ESPFileServer</h1>
	</div>
</div>

<div class="flex grow flex-col">
	<div>
		<Folder name="/" size="" files={root} expanded />
	</div>
	<div class="flex grow" />
	<div class="flex flex-col p-3 items-center">
		<div>
			Icons by <a href="https://iconoir.com/">Iconoir</a>.
		</div>
		<div>
			© {currentYear} Noran Raskin.
		</div>
	</div>
</div>
