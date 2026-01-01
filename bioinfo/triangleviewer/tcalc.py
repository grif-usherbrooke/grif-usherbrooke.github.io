from flask import Flask, request
import os
import subprocess

app = Flask(__name__, template_folder='')


@app.route("/")
def home():
    #return os.getcwd()
    #return render_template('test.html')
    return app.send_static_file('test.html')


@app.route("/tcalc")
def tcalc():
    #example: http://localhost:5000/tcalc?mg=0.5&hg=1&wg=0.1&ma=0.5&ha=1&wa=0.1&mb=0.7&hb=1&wb=0.1
    
    mg = request.args.get('mg')
    hg = request.args.get('hg')
    wg = request.args.get('wg')
    ma = request.args.get('ma')
    ha = request.args.get('ha')
    wa = request.args.get('wa')
    mb = request.args.get('mb')
    hb = request.args.get('hb')
    wb = request.args.get('wb')
    
    return (subprocess.check_output(['triangle_calc.exe', mg, hg, wg, ma, ha, wa, mb, hb, wb]))
    
    

if __name__ == "__main__":
    app.run()