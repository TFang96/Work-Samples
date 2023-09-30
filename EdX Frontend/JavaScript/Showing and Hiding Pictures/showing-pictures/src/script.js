let myPicturesArray = [
{
"albumId": 1,
"id": 1,
"title": "New York",
"url": "https://ihg.scene7.com/is/image/ihg/nycpc-nyc-skyline-1440x720"
},
{
"albumId": 1,
"id": 2,
"title": "Los Angeles",
"url": "https://lacounty.gov/wp-content/uploads/2022/03/shutterstock_1418018357-scaled.jpg"
},
{
"albumId": 2,
"id": 51,
"title": "Chicago",
"url": "https://www.nationsonline.org/gallery/USA/Buildings-along-Chicago-River.jpg"
},
{
"albumId": 2,
"id": 52,
"title": "San Francisco",
"url": "https://media.bizj.us/view/img/11637667/sanfranciscoskyline032620tj-1*xx7360-4140-0-384.jpg"
},
{
"albumId": 3,
"id": 127,
"title": "Las Vegas",
"url": "https://assets.simpleviewcms.com/simpleview/image/upload/c_limit,h_1200,q_75,w_1200/v1/clients/lasvegas/strip_b86ddbea-3add-4995-b449-ac85d700b027.jpg"
},
{
"albumId": 3,
"id": 128,
"title": "Reno",
"url": "https://www.treksplorer.com/wp-content/uploads/things-to-do-in-reno.jpg"
}
];


function Display() {
  Hide();
  myPicturesArray.forEach(function(currentImage) {
   let image = document.createElement("img");
   let description = document.createElement("figcaption");
   description.innerHTML = currentImage.title;
   image.src = currentImage.url;
   image.alt = currentImage.title;
   image.width = 500;
   image.height = 500;
   document.body.append(document.createElement("br"));
   document.body.append(image);
   document.body.append(description);
});
  let descriptions = document.getElementsByTagName('figcaption');
  let total = descriptions.length;
}

// Hide images
function Hide() {
  let breaks = document.getElementsByTagName('br');
  let pictures = document.getElementsByTagName('img');
  let descriptions = document.getElementsByTagName('figcaption');
  let removed = 0;
  console.log("Number of br: " + breaks.length);
  console.log("Number of pictures: " + pictures.length);
  console.log("Descriptions: " + descriptions.length);
  for(let i = 0; i < breaks.length; i++) {
    breaks[i].remove();
    i--;
  }
  for(let i = 0; i < pictures.length; i++) {
    pictures[i].remove();
    i--;
  }
  for(let i = 0; i < descriptions.length; i++) {
    removed++;
    console.log("Removing: " + descriptions[i].innerHTML);
    descriptions[i].remove();
    i--
  }
  console.log("Removed: " + removed + " descriptions in iteration..");
}