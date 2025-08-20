/** @returns {Promise<import('jest').Config} */
module.exports = async () => {
  return {
    transform: {
      '\\.js$': [
        'babel-jest',
        {
          configFile: './babel.config.test.json',
        },
      ],
    },
    reporters: [
      'default',
      [
        'jest-junit',
        {
          outputDirectory: 'test-results',
          outputName: 'jest-junit-report.xml',
        },
      ],
    ],
    coverageDirectory: 'test-results/jest-coverage',
    collectCoverageFrom: [
      'modules/custom/gofast_core/**/*.js',
      'themes/gofast/**/*.js',
      '!**/{dist,build}/**/*.js',
      '!**/keen/**',
      '!**/node_modules/**',
      '!**/*.{test,config}.js',
      '!**/app.js',
    ],
    coverageReporters: ['html', 'text', 'text-summary', 'cobertura'],
    testMatch: ['**/*.test.js'],
  };
};
