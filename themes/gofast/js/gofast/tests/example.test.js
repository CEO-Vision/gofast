// We import the globals so ESLint does not flag them as errors later.
// We can configure it so it's not necessary
// Babel is run on test files before execution allowing using ESModule syntax.
// The files run are ultimately using commonJS however.
import { describe, it, expect } from '@jest/globals';
// Import functionality to test from other modules. Webpack is not configured to
// run so only js files are supported.
import { unit } from './example_module';

// The "tests" directory does not affect how tests are found, test file may
// exist next to the file implementing the tested functionality, so long as its
// filename ends in .test.js (can be configured)

// `describe` creates a group for tests
describe('Example tests', () => {
  // `it` creates a test case. Alternatively, `test` can be used. If anything
  // is thrown inside the test, it fails
  it('always passes', () => {
    // Assertions use an expect syntax.
    expect(true).toBeTruthy();
  });

  // test groups can be nested
  describe('unit function', () => {
    // Adding comments to structure tests using Given When Then can improve
    // readability.
    it('returns its argument', () => {
      // Given
      const value = 42;
      // When
      const result = unit(value);
      // Then
      expect(result).toBe(value);
    });
  });
});
