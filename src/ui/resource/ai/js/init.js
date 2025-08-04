document.addEventListener('DOMContentLoaded', function () {
    initResizeHandle();
    initGuide();
    initInputContainer();

    document.addEventListener('click', () => {
        clearMenu();
    });
});

function clearMenu() {
    document.querySelectorAll('.menu-popup').forEach(popup => {
        popup.classList.remove('show');
    });

    const uploadMenu = document.getElementById('upload-menu');
    if (uploadMenu) {
        uploadMenu.classList.remove('show');
    }
}

function setWelcomeState(visible) {

}