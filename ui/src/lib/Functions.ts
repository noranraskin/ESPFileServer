

export function downloadFile(path: string, filename: string) {
    // const url = window.location.host + "/espfileserver-download-file" + path + "/" + filename;
    const url = "http://10.10.20.159" + "/espfileserver-download-file" + (path == '/' ? "" : path) + "/" + filename;
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