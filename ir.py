from PIL import Image
from PIL import ImageEnhance
im = Image.open(r"Z:\sem 6\CG Lab\images\luca.jpg")
# im.show()


r,b,g = im.split()
r.save("redLUCA.jpeg")
g.save("greenLUCA.jpeg")
b.save("blueLUCA.jpeg")

# im = Image.merge("RGB", (b,g,r));
# im.show()

# b/w
with Image.open(r"Z:\sem 6\CG Lab\images\alone-concept.webp"):
    i=im.convert("L")
# im.show()
i.save("bwLUCA.jpeg")

#resize
out = im.resize((128,128))
# out.show()
out = im.rotate(45)
# out.show()

#crop
box = (100,100,200,200)
reg = im.crop(box)
# reg.show()

#transpose
out = im.transpose(Image.FLIP_LEFT_RIGHT)
# out.show()
out = im.transpose(Image.FLIP_TOP_BOTTOM)
# out.show()
out = im.transpose(Image.ROTATE_90)
# out.show()


#imgae enhancement
eeh= ImageEnhance.Contrast(im)
eeh.enhance(0.3).show()
