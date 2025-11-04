(function(){function isElementVisible(el){if(!el)return false;const style=window.getComputedStyle(el);return style.display!=='none'&&style.visibility!=='hidden'&&el.offsetHeight>0;}
function findFunctionBlock(start){var el=start;for(var i=0;i<5&&el;i++){if(el.classList){if(el.classList.contains('function')||el.classList.contains('memitem')||el.classList.contains('section')){return el;}}
el=el.parentElement;}
el=start.nextElementSibling;while(el){if(el.classList&&(el.classList.contains('function')||el.classList.contains('memitem')||el.classList.contains('section'))){return el;}
el=el.nextElementSibling;}
return null;}
function scrollToVisibleFunctionAnchor(){if(!window.location.hash)return;var hash=window.location.hash.substring(1);var target=document.getElementById(hash);if(!target)return;if(!isElementVisible(target)||target.offsetHeight<5){var block=findFunctionBlock(target);if(block){block.scrollIntoView({behavior:'auto',block:'center'});console.log('[fix_doxygen_scroll] Scrolled to function block for anchor #'+hash);}else{console.log('[fix_doxygen_scroll] No visible function block found for anchor #'+hash);}}}
window.addEventListener('DOMContentLoaded',function(){setTimeout(scrollToVisibleFunctionAnchor,300);});window.addEventListener('hashchange',function(){setTimeout(scrollToVisibleFunctionAnchor,100);});})();