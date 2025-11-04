function navigateToURL(url,fallbackURL)
{fetch(url,{method:'HEAD'}).then(response=>{if(response.ok){window.location.href=url;}else{console.warn("The requested page does not exist in the selected version. Redirecting to the fallback URL.");window.location.href=fallbackURL;}}).catch(()=>{console.error("Network error.");window.location.href=fallbackURL;});}
function navigateToURL_offline(url,fallbackURL)
{console.warn("This is the local test version: blind jump to the target URL")
console.warn("Replace me by: navigateToURL")
window.location.href=url;}
function switchVersion(version,fallbackURL)
{event.preventDefault();var currentURL=window.location.href;console.log("Current URL:",currentURL);console.log("Fallback URL:",fallbackURL);var targetURL="";if(currentURL.includes('/_prev/'))
{if(version==='latest')
{console.log("from prev to latest")
try{var match=currentURL.match(/(.*\/)_prev\/[a-zA-Z0-9_-]+\/(.*\.html.*)/);if(match&&match.length>2){targetURL=match[1]+match[2];}else{console.error("URL match failed. Invalid format or structure.");targetURL=fallbackURL;}}catch(error){console.error("Error constructing targetURL for latest version:",error);targetURL=fallbackURL;}}
else
{console.log("from prev to prev")
targetURL=currentURL.replace(/(.*\/)_prev\/[a-zA-Z0-9_-]+\/(.*\.html)/,'$1'+'_prev/'+version+'/$2');if(currentURL===targetURL)
{console.warn("replaces nothing: fallbackURL = ",fallbackURL)
targetURL=fallbackURL;}}}
else
{if(version==='latest')
{console.log("from latest to latest")
targetURL=currentURL;}
else
{console.log("from latest to prev")
if(currentURL.includes('/i18n/'))
{targetURL=currentURL.replace(/(.*\/)(i18n\/.*\.html)/,'$1'+'_prev/'+version+'/$2');}
else
{targetURL=currentURL.replace(/(.*\/)(docs\/.*\.html)/,'$1'+'_prev/'+version+'/$2');}
if(targetURL==currentURL)
{console.log("from latest to prev: home page")
targetURL=currentURL.replace(/(.*\/)(.*\.html)/,'$1'+'_prev/'+version+'/$2');if(currentURL===targetURL)
{console.warn("replaces nothing: fallbackURL = ",fallbackURL)
targetURL=fallbackURL;}}}}
console.log("Target URL:",targetURL);navigateToURL_offline(targetURL,fallbackURL);}