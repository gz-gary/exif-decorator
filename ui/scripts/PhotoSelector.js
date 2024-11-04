document.addEventListener('DOMContentLoaded', () => {
    const button1 = document.getElementById('button1');
    const button2 = document.getElementById('button2');
    const fileInput = document.getElementById('fileInput');
    const fileOutput = document.getElementById('fileOutput');
    const leftDiv = document.getElementById('leftDiv');
    const framedPhoto = document.getElementById('framedPhoto');

    let rawPhotoPath = "";

    button1.addEventListener('click', () => {
        fileInput.click();
    });

    fileInput.addEventListener('change', (event) => {
        const file = event.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = (e) => {
                const imageUrl = e.target.result;
                // Update the background image
                const backgroundPhoto = document.getElementById('backgroundPhoto');
                backgroundPhoto.src = imageUrl;
                
                // Update the framed photo
                framedPhoto.src = imageUrl;
            };
            reader.readAsDataURL(file);
        }
    });

    button2.addEventListener('click', () => {
        fileOutput.click();
    });

    fileOutput.addEventListener('change', (event) => {
        const file = event.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onloadend = function() {  
                const base64data = reader.result.split(',')[1]; // Extract base64 data
                fetch('/upload-raw', {  
                    method: 'POST',  
                    headers: {  
                        'Content-Type': 'application/json',  
                    },  
                    body: JSON.stringify({ file: base64data }) // Send only the base64 data to the backend  
                })  
                .then(response => response.json())  
                .then(data => console.log('success:', data))  
                .catch(error => console.error('fail:', error));  
            }; 
            reader.readAsDataURL(file);
        }
    });
});