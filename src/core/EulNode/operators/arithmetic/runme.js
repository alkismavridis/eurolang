const fs = require('fs');


const fileEntities = [
  "BinOrOperator",
  "BinAndOperator",
  "LeftShiftOperator",
  "RightShiftOperator",
  "PlusOperator",
  "PercentOperator",
  "StarOperator",
  "SlashOperator",
  "TildeOperator",
];
// fs.readdirSync("./").forEach(file => {
//   if(!file.endsWith(".h")) return;
//
//   const stats = fs.statSync(file);
//   if(stats.isDirectory()) return;
//
//   fileEntities.push(file);
// });

//1, Create the new directories
fileEntities.forEach(file => {
  const dirName = file;
  fs.mkdirSync(dirName);

  const generatedH = dirName + "/" + dirName+".h";
  fs.writeFileSync(generatedH, "#pragma once\n\n\n");

  const generatedImpl = dirName + "/" + dirName+".impl.h";
  fs.writeFileSync(generatedImpl, "#pragma once\n\n\n//region LIFE CYCLE\n//endregion\n\n\n//region CORE FUNCTIONS\n//endregion\n\n\n//region CODE GENERATION\n//endregion\n\n\n//region SERIALIZATION\n//endregion\n\n\n");
});
