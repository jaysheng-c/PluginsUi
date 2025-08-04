const GuideState = {
    isExpand: true
}

// 初始化导航栏
function initGuide() {
    const sidebar = document.getElementById('sidebar');
    const guideBtn = document.getElementById('guide-btn');
    if (guideBtn) {
        guideBtn.addEventListener('click', function() {
            const chatAddBtn = document.getElementById('new-chat-btn-header');
            sidebar.classList.add('animating');
            GuideState.isExpand = !GuideState.isExpand;
            const guideBtnIcon = document.querySelector('.guide-btn-icon');
            if (GuideState.isExpand) {
                sidebar.classList.remove('collapsed');
                guideBtnIcon.src = PngPrefix + PngFiles.guideShrinkPng;
                guideBtnIcon.alt = PngFiles.guideShrinkPng;
                if (chatAddBtn) {
                    chatAddBtn.style.display = 'flex';
                }
            } else {
                sidebar.classList.add('collapsed');
                guideBtnIcon.src = PngPrefix + PngFiles.guideExpandPng;
                guideBtnIcon.alt = PngFiles.guideExpandPng;
                if (chatAddBtn) {
                    chatAddBtn.style.display = 'none';
                }
            }
        });
        // 动画结束后移除类
        sidebar.addEventListener('transitionend', function handler() {
            sidebar.classList.remove('animating');
            // sidebar.removeEventListener('transitionend', handler);
        });
    }
    initComponent();
}

function initComponent() {
    document.getElementById('group-component').addEventListener('click', function(e) {
        const clickedItem = e.target.closest('.chat-component-item');
        if (clickedItem) {
            document.querySelectorAll('.chat-component-item').forEach(item => {
                if (clickedItem !== item) {
                    item.classList.remove('active');
                }
            });
            clickedItem.classList.add('active');
            // TODO: checkGroup(clickedItem.id)
        }
    });

    document.getElementById('chat-component').addEventListener('click', function(e) {
        const clickedItem = e.target.closest('.chat-component-item');
        if (clickedItem) {
            document.querySelectorAll('.chat-component-item').forEach(item => {
                if (clickedItem !== item) {
                    item.classList.remove('active');
                }
            });
            clickedItem.classList.add('active');
            // TODO: checkChat(clickedItem.id)
        }
    });
}

//
function menuClick(event, menu) {
    const item = menu.parentElement;
    if (!item) {
        return;
    }
    event.stopPropagation();
    // FIXME: 菜单栏的弹出位置有bug，后续修复
    const menuPopup = item.querySelector('.menu-popup');
    if (menuPopup) {
        const isShowing = menuPopup.classList.contains('show');
        clearMenu();
        menuPopup.classList.toggle('show', !isShowing);
    }
}

// 新增聊天
let chatItemIdx = 0;
function addChat() {
    console.log("addChat");
    const chat = document.getElementById('chat-component');
    if (!chat) {
        return;
    }
    const item = document.createElement('div');
    // item.className = 'chat-component-item active';
    item.className = 'chat-component-item';
    item.id = `chat-${Date.now()}`;
    item.innerHTML = `
        <div class="text">聊天${chatItemIdx + 1}</div>
        <div class="chat-component-menu" onclick="menuClick(event, this)">
            <span class="menu-dots"></span>
        </div>
        <div class="menu-popup">
            <div class="menu-item">
                <img src="${PngPrefix + PngFiles.toTopPng}" alt='${PngFiles.toTopPng}'>
                <span class="menu-item-text">置顶</span>
            </div>
            <div class="menu-item">
                <img src="${PngPrefix + PngFiles.renamePng}" alt='${PngFiles.renamePng}'>
                <span class="menu-item-text">重命名</span>
            </div>
            <div class="menu-item delete">
                <img src="${PngPrefix + PngFiles.deletePng}" alt='${PngFiles.deletePng}'>
                <span class="menu-item-text">删除</span>
            </div>
        </div>
    `
    // 取消其他项的active状态
    document.querySelectorAll('.chat-component-item').forEach(item => {
        item.classList.remove('active');
    });
    chat.append(item);

    chatItemIdx++;
}

// 添加组
let groupItemIdx = 0;
function addGroup() {
    console.log("addGroup");
    const group = document.getElementById('group-component');
    if (!group) {
        return;
    }
    const item = document.createElement('div');
    // item.className = 'chat-component-item active';
    item.className = 'chat-component-item';
    item.id = `group-${Date.now()}`;
    item.innerHTML = `
        <div class="text">
            <img src="${PngPrefix + PngFiles.groupPng}" alt="${PngFiles.groupPng}">
            <span>分组${groupItemIdx + 1}</span>
        </div>
        <div class="chat-component-menu" onclick="menuClick(event, this)">
            <span class="menu-dots"></span>
        </div>
        <div class="menu-popup">
            <div class="menu-item">
                <img src="${PngPrefix + PngFiles.toTopPng}" alt="${PngFiles.toTopPng}">
                <span class="menu-item-text">置顶</span>
            </div>
            <div class="menu-item">
                <img src="${PngPrefix + PngFiles.renamePng}" alt="${PngFiles.renamePng}">
                <span class="menu-item-text">重命名</span>
            </div>
            <div class="menu-item delete">
                <img src="${PngPrefix + PngFiles.deletePng}" alt="${PngFiles.deletePng}">
                <span class="menu-item-text">删除</span>
            </div>
        </div>
    `
    // 取消其他项的active状态
    document.querySelectorAll('.chat-component-item').forEach(item => {
        item.classList.remove('active');
    });
    group.append(item);

    groupItemIdx++;
}