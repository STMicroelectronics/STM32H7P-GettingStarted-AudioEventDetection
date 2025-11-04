function escapeRegExp(string){return string.replace(/[.*+?^${}()|[\]\\]/g,'\\$&');}
export function filterText(target,exclude){const clone=target.cloneNode(true);if(exclude){clone.querySelectorAll(exclude).forEach(node=>node.remove());}
return clone.innerText;}
export function formatCopyText(textContent,copybuttonPromptText,isRegexp=false,onlyCopyPromptLines=true,removePrompts=true,copyEmptyLines=true,lineContinuationChar="",hereDocDelim=""){var regexp;var match;var useLineCont=!!lineContinuationChar
var useHereDoc=!!hereDocDelim
if(isRegexp){regexp=new RegExp('^('+copybuttonPromptText+')(.*)')}else{regexp=new RegExp('^('+escapeRegExp(copybuttonPromptText)+')(.*)')}
const outputLines=[];var promptFound=false;var gotLineCont=false;var gotHereDoc=false;const lineGotPrompt=[];for(const line of textContent.split('\n')){match=line.match(regexp)
if(match||gotLineCont||gotHereDoc){promptFound=regexp.test(line)
lineGotPrompt.push(promptFound)
if(removePrompts&&promptFound){outputLines.push(match[2])}else{outputLines.push(line)}
gotLineCont=line.endsWith(lineContinuationChar)&useLineCont
if(line.includes(hereDocDelim)&useHereDoc)
gotHereDoc=!gotHereDoc}else if(!onlyCopyPromptLines){outputLines.push(line)}else if(copyEmptyLines&&line.trim()===''){outputLines.push(line)}}
if(lineGotPrompt.some(v=>v===true)){textContent=outputLines.join('\n');}
if(textContent.endsWith("\n")){textContent=textContent.slice(0,-1)}
return textContent}