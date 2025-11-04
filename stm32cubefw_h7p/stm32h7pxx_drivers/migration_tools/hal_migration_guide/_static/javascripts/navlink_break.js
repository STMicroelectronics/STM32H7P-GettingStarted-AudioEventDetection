(function(){function insertBreaksInCamelCase(text){const exceptions=["STM32CubeMX2","FreeRTOS","NetX","FileX","LevelX"];if(exceptions.some(exception=>text.includes(exception))){return text;}
else{return text.replace(/([a-z])([A-Z])/g,'$1<wbr>$2');}}
function insertBreaksInSnakeCase(text){return text.replace(/_/g,'_<wbr>');}
function modifyNavLinksWithBreakOpportunities(){const links=document.querySelectorAll('.md-nav__link');links.forEach(link=>{let text=link.textContent;text=insertBreaksInCamelCase(text);text=insertBreaksInSnakeCase(text);link.innerHTML=text;});}
document.addEventListener('DOMContentLoaded',modifyNavLinksWithBreakOpportunities);})();