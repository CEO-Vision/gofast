const path = require('path');

module.exports = {
    entry: [
        __dirname + '/src/index.js',
        __dirname + '/src/scss/style.scss'
    ],
    output: {
        path: path.resolve(__dirname, 'dist'), 
        filename: 'js/app.min.js',
    },
    mode: 'production',
    module: {
        rules: [
            {
                test: /\.js$/,
                exclude: /node_modules/,
                use: [],
            }, 
            {
                test: /\.scss$/,
                exclude: /node_modules/,
                use: [
                    {
                        loader: 'file-loader',
                        options: { outputPath: 'css/', name: 'style.min.css'}
                    },
                    'sass-loader'
                ]
            }, 
            {
                test: /\.(png|jpg)$/,
                exclude: /node_modules/,
                use: [
                    {
                        loader: 'file-loader'
                    }
                ]
            }

        ], 
    }
};

  
  