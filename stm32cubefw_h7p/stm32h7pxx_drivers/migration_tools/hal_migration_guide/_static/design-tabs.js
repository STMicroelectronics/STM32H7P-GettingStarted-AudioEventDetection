let sd_id_to_elements={};const storageKeyPrefix="sphinx-design-tab-id-";function create_key(el){let syncId=el.getAttribute("data-sync-id");let syncGroup=el.getAttribute("data-sync-group");if(!syncId||!syncGroup)return null;return[syncGroup,syncId,syncGroup+"--"+syncId];}
function ready(){let groups=[];document.querySelectorAll(".sd-tab-label").forEach((label)=>{if(label instanceof HTMLElement){let data=create_key(label);if(data){let[group,id,key]=data;label.onclick=onSDLabelClick;if(!sd_id_to_elements[key]){sd_id_to_elements[key]=[];}
sd_id_to_elements[key].push(label);if(groups.indexOf(group)===-1){groups.push(group);const tabParam=new URLSearchParams(window.location.search).get(group);if(tabParam){console.log("sphinx-design: Selecting tab id for group '"+
group+"' from URL parameter: "+
tabParam);window.sessionStorage.setItem(storageKeyPrefix+group,tabParam);}}
let previousId=window.sessionStorage.getItem(storageKeyPrefix+group);if(previousId===id){label.previousElementSibling.checked=true;}}}});}
function onSDLabelClick(){let data=create_key(this);if(!data)return;let[group,id,key]=data;for(const label of sd_id_to_elements[key]){if(label===this)continue;label.previousElementSibling.checked=true;}
window.sessionStorage.setItem(storageKeyPrefix+group,id);}
document.addEventListener("DOMContentLoaded",ready,false);