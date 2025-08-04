function initInputContainer() {
    const userInput = document.getElementById('user-input');
    const sendBtn = document.getElementById('send-btn');
    const stopBtn = document.getElementById('stop-btn');

    userInput.addEventListener('keypress', function(e){
        if (e.key === 'Enter' && !e.shiftKey) {
            e.preventDefault();
            if (sendBtn) {
                sendBtn.click();
            }
        }
    });
    userInput.addEventListener('input', adjustInputHeight);
    sendBtn.addEventListener('click', sendMsg);
    stopBtn.addEventListener('click', stopMsg);

    setSendState(false);
}

function setSendState(sending) {
    const sendBtn = document.getElementById('send-btn');
    const stopBtn = document.getElementById('stop-btn');
    sendBtn.style.display = sending ? 'none' : 'block';
    stopBtn.style.display = !sending ? 'none' : 'block';
}

function adjustInputHeight() {
    const input = document.getElementById('user-input');
    input.style.height = 'auto';
    const newHeight = Math.min(input.scrollHeight, 120);
    input.style.height = newHeight + 'px';

    // 根据是否需要滚动条来添加/移除类
    if (input.scrollHeight > newHeight) {
        input.classList.add('scrollable');
    } else {
        input.classList.remove('scrollable');
    }
}

function checkState() {
    return false;
}

// 处理用户信息
function processUserMessage(text) {

}

function fileUploadBtn(event) {
    event.stopPropagation();
    const uploadMenu = document.getElementById('upload-menu');
    const isShowing = uploadMenu.classList.contains('show');

    clearMenu();

    // 隐藏所有其他菜单
    document.querySelectorAll('.upload-menu').forEach(menu => {
        if (menu !== uploadMenu) menu.classList.remove('show');
    });

    uploadMenu.classList.toggle('show', !isShowing);
}

function sendMsg() {
    const userInput = document.getElementById('user-input');
    const message = userInput.value.trim();
    // if (!checkedState()) {
    //     return;
    // }
    if (message) {
        console.log(message);

        setWelcomeState(false);
        processUserMessage(message);

        // TODO: 发送消息到后台，并且启动接收

        userInput.value = '';
        setSendState(true);
    }
}

function stopMsg() {
    setSendState(false);

    // TODO: 暂替消息接受
}



