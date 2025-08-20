<?php

namespace Drupal\Tests\gofast_core\Unit;

use Drupal\Tests\UnitTestCase;

/**
 * Demo unit test class.
 *
 * The test classes' names must all end with 'Test'
 *
 * @package Drupal\Tests\gofast_core\Unit
 */
final class AlwaysPassTest extends UnitTestCase {

  /**
   * Demo test case function that should always pass.
   *
   * Test cases names must start with 'test' to be detected.
   *
   * @return void
   *   no return value
   */
  public function testTrueIsTrue() {
    // Assertions are found on the test case instance.
    $this->assertTrue(TRUE);
  }

}
