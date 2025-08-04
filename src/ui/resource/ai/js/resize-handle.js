const ResizeHandleState = {
    isResizing: false,
    handle: null
}

function initResizeHandle() {
    const resizeHandle = document.getElementById('resize-handle');
    resizeHandle.addEventListener('mousedown', handlePressed);
}

function handlePressed(e) {
    ResizeHandleState.handle = e.target;
    ResizeHandleState.isResizing = true;
    document.body.style.cursor = 'col-resize';
    document.addEventListener('mousemove', handleMouseMove);
    document.addEventListener('mouseup', stopResize);
    e.preventDefault();
    console.log(ResizeHandleState.handle.id);
}

function handleMouseMove(e) {
    if (ResizeHandleState.handle === null || !ResizeHandleState.isResizing) {
        return;
    }
    if (ResizeHandleState.handle.id === 'resize-handle') {
        const sidebar = document.getElementById('sidebar');
        const mainContainer = document.getElementById('main-container');
        if (!sidebar || !mainContainer) {
            console.warn('Could not find main-container or sidebar.');
            return;
        }
        const mainRect = mainContainer.getBoundingClientRect();
        const guideNewWidth = e.clientX - mainRect.left;
        const minWidth = parseInt(sidebar.style.minWidth) || 200;
        const maxWidth = parseInt(sidebar.style.maxWidth) || 400;

        if (guideNewWidth >= minWidth && guideNewWidth <= maxWidth) {
            sidebar.style.width = `${guideNewWidth}px`;
        }

    }
}

function stopResize() {
    ResizeHandleState.handle = null;
    ResizeHandleState.isResizing = false;
    document.body.style.cursor = '';
    document.removeEventListener('mousemove', handleMouseMove);
    document.removeEventListener('mouseup', stopResize);
}