const GuideState = {
    isExpand: true
}
function initGuide() {
    const sidebar = document.getElementById('sidebar');
    const guideBtn = document.getElementById('guide-btn');
    if (guideBtn) {
        guideBtn.addEventListener('click', function() {
            sidebar.classList.add('animating');
            GuideState.isExpand = !GuideState.isExpand;
            const guideBtnIcon = document.querySelector('.guide-btn-icon');
            if (GuideState.isExpand) {
                sidebar.classList.remove('collapsed');
                guideBtnIcon.src = './image/guide-btn-shrink.png'
            } else {
                sidebar.classList.add('collapsed');
                guideBtnIcon.src = './image/guide-btn-expand.png'
            }
        });
        // 动画结束后移除类
        sidebar.addEventListener('transitionend', function handler() {
            console.log("1111");
            sidebar.classList.remove('animating');
            // sidebar.removeEventListener('transitionend', handler);
        });
    }
}