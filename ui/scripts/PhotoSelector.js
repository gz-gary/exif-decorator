document.addEventListener('DOMContentLoaded', () => {
    const button1 = document.getElementById('button1');
    const fileInput = document.getElementById('fileInput');
    const leftDiv = document.getElementById('leftDiv');

    button1.addEventListener('click', () => {
        fileInput.click();
    });

    fileInput.addEventListener('change', (event) => {
        const file = event.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = (e) => {
                leftDiv.style.backgroundImage = `url(${e.target.result})`;
            };
            reader.readAsDataURL(file);
        }
    });
});