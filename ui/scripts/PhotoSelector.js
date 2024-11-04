document.addEventListener('DOMContentLoaded', () => {
    const button1 = document.getElementById('button1');
    const button2 = document.getElementById('button2');
    const button3 = document.getElementById('button3');
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
                
                // Show the loading popup
                document.getElementById('loadingPopup').style.display = 'flex'; // Use 'flex' to activate Flexbox

                fetch('/upload-raw', {  
                    method: 'POST',  
                    headers: {  
                        'Content-Type': 'application/json',  
                    },  
                    body: JSON.stringify({ file: base64data }) // Send only the base64 data to the backend  
                })  
                .then(response => response.json())  
                .then(data => {
                    console.log('success:', data);
                    // Hide the loading popup
                    document.getElementById('loadingPopup').style.display = 'none';
                })  
                .catch(error => {
                    console.error('fail:', error);
                    // Hide the loading popup
                    document.getElementById('loadingPopup').style.display = 'none';
                });  
            }; 
            reader.readAsDataURL(file);
        }
    });

    // Button 3: Save leftDiv as image using dom-to-image
    button3.addEventListener('click', () => {
        const leftDiv = document.getElementById('leftDiv');
        
        // Show the loading popup
        document.getElementById('loadingPopup').style.display = 'flex';

        domtoimage.toPng(leftDiv)
            .then(function (dataUrl) {  
                // 创建一个链接并下载图片  
                const link = document.createElement('a');  
                link.download = 'screenshot.png'; // 指定下载的文件名  
                link.href = dataUrl;  
                link.click(); // 自动点击链接以触发下载  
                document.getElementById('loadingPopup').style.display = 'none';
            })  
            .catch(function (error) {  
                console.error('oops, something went wrong!', error);  
                document.getElementById('loadingPopup').style.display = 'none';
            });
    });
});