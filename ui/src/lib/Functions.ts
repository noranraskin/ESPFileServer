import { writable } from "svelte/store";

export const totalBytes = writable(0);
export const usedBytes = writable(0);
export const isDragging = writable(false);
export const dragOffsetX = writable(0);
export const dragOffsetY = writable(0);
export const draggedItem = writable(null);
export const isMoving = writable(false);
export const itemUnderCursor = writable<Array<string>>([]);
export const draggedItemPath = writable("");
export const draggedItemName = writable("");
export const FS = writable<Array<object>>([]);

// const hostURL = window.location.host;
// const hostURL = "http://localhost:8080";
const hostURL = "http://10.10.20.159";


export function downloadFile(path: string, filename: string) {
    // const url = window.location.host + "/espfileserver-download-file" + path + "/" + filename;
    const url = hostURL + "/espfileserver-download-file" + (path == '/' ? "" : path) + "/" + filename;
    fetch(url)
        .then(response => response.blob())
        .then(blob => {
            const url = window.URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.href = url;
            a.download = filename;
            a.click();
            window.URL.revokeObjectURL(url);
        });
}

// export function downloadFolder(folder, path: string, filename = "") {
//     const name = (filename == "" ? filename : filename + '/' ) + folder.name;
//     if (folder.files) {
//         folder.files.forEach((file) => {
//             downloadFolder(file, path, name)
//         });
//     } else {
//         downloadFile(path, name);
//     }
// }

export function loadListOfFiles() {
    const url = hostURL + "/espfileserver-get-list-of-all-files";
    fetch(url)
        .then(response => response.json())
        .then(data => {
            FS.set(data);
            updateFSInfo();
        })
}

export function renameFile(oldPath: string, newPath: string) {
    const url = hostURL + "/espfileserver-move-file?from=" + oldPath + "&to=" + newPath;
    fetch(url, { method: 'POST' })
        .then(response => {
            response.ok ? console.log("File renamed") : alert("Error renaming file");
            loadListOfFiles();
        })
}

export function updateFSInfo() {
    const url = hostURL + "/espfileserver-get-fs-info";
    fetch(url)
        .then(response => response.json())
        .then(data => {
            totalBytes.set(data.totalBytes);
            usedBytes.set(data.usedBytes);
        })
}