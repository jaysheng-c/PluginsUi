document.addEventListener('DOMContentLoaded', function () {
    // 初始化 marked 和 highlight.js
    marked.setOptions({
        breaks: true,
        highlight: function(code, lang) {
            const validLang = hljs.getLanguage(lang) ? lang : 'plaintext';
            return hljs.highlight(code, { language: validLang }).value;
        }
    });
    initResizeHandle();
    initGuide();
    initInputContainer();

    document.querySelectorAll('.img').forEach(img => {
        img.src = PngPrefix + img.alt;
    });

    document.addEventListener('click', () => {
        clearMenu();
    });
});

function escapeHtml(unsafe) {
    return unsafe
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;");
}

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