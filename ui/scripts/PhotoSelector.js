document.addEventListener('DOMContentLoaded', () => {
    const button1 = document.getElementById('button1');
    const fileInput = document.getElementById('fileInput');
    const leftDiv = document.getElementById('leftDiv');
    const framedPhoto = document.getElementById('framedPhoto');

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
});