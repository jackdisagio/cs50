import os
import qrcode

image = qrcode.make("https://www.youtube.com/watch?v=xvFZjo5PgG0&list=RDxvFZjo5PgG0&start_radio=1")

image.save("qr.PNG")
