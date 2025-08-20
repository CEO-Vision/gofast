const path = require('path');
const glob = require('glob');
const { VueLoaderPlugin } = require('vue-loader');
const { CleanWebpackPlugin } = require('clean-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const { BundleAnalyzerPlugin } = require('webpack-bundle-analyzer');
const CompressionPlugin = require('compression-webpack-plugin');
const Dotenv = require('dotenv-webpack');

// Find all applications under ./src/apps/*
const entryPoints = glob.sync('./src/apps/**/app.js').reduce((acc, path) => {
  const entry = path.split('/')[2];
  acc[entry] = `./${path}`;
  return acc;
}, {});

module.exports = {
  mode: 'development', // ou 'production' pour la production
  entry: entryPoints,
  output: {
    path: path.resolve(__dirname, 'dist/'),
    filename: '[name].js',
  },
  module: {
    rules: [
      {
        test: /\.vue$/, // Traitement des fichiers Vue
        loader: 'vue-loader',
      },
      {
        test: /\.js$/, // Transpiler les fichiers JavaScript avec Babel
        exclude: path.resolve('node_modules'),
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env'],
          },
        },
      },
      {
        test: /\.css$/,
        use: [MiniCssExtractPlugin.loader, 'css-loader'],
      },
    ],
  },
  optimization: {
    splitChunks: {
      cacheGroups: {
        default: false, // Désactiver la création automatique de chunks
        vendors: {
          test: /[\\/]node_modules[\\/](vue|jquery)[\\/]/,
          name: 'vendors',
          chunks: 'all',
          enforce: true, // Forcer la création de ce chunk
        },
        survey: {
          test: /[\\/]node_modules[\\/]survey-.*/, // Inclure tous les fichiers qui commencent par 'survey'
          name: 'survey',
          chunks: 'all',
          enforce: true, // Forcer la création de ce chunk
        },
      },
    },
  },
  plugins: [
    new CleanWebpackPlugin(),
    new VueLoaderPlugin(),
    new MiniCssExtractPlugin({
      filename: '[name].css',
    }),
    // new BundleAnalyzerPlugin(),
    new CompressionPlugin({
      test: /\.(js|css|html|svg)$/,
      algorithm: 'gzip',
      threshold: 10240, // Seuls les fichiers supérieurs à 10 Ko seront compressés
      minRatio: 0.8,
    }),
    new Dotenv(),
  ],
  resolve: {
    extensions: ['.js', '.vue'], // Permet de résoudre automatiquement les extensions .js et .vue
    alias: {
      vue: 'vue/dist/vue.esm-bundler.js', // Utilise la version runtime de Vue.js pour la compilation avec vue-loader
    },
  },
};
