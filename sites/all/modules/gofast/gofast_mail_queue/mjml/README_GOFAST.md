MJML is a node module helping templating emails faster.

# Installation
1. `npm install` from this folder on the development server to install dependencies
2. add `mjml` to your PATH: `export PATH="$PATH:./node_modules/.bin"`

# Usage
- Use existing .mjml files as models or go to the [official documentation](https://documentation.mjml.io/)
- The official MJML VSCode plugin provides many templates as well as a live preview tool

## Desktop Outlook specific conventions
- all line jumps not ensured by <mj-text> or <mj-button> tags should be ensured by <mj-section> tags
- prefer <b> and <i> tags to <strong> and <em>
- to ensure alignment, wrap small inline elements inside mj-text > table[padding=0 cellspacing=0 cellpading=0 role="presentation" style="vertical-align: top|middle|bottom;"] > tbody > tr > td ; you should then duplicate style properties in a span inside the td not to lose them ; colors inside the table tag should be hexadecimal and dimensions in px
- img can only be dimensioned with a width attribute without a specific unit declaration
- color property should be placed _before_ text-decoration in inline styles

# Compilation
0. if you are just updating a template, don't hesitate to diff the output between the current template and insert only the changes
1. always use in your template body the same width used in the header body
2. mjml filename.mjml > output.html
3. move the output to the ../tpl folder and adapt it as a Drupal .tpl.php file (by replacing static content with dynamic content)
4. keep only the relevant sections of your template _and_ the style tags, which are very important for MJML classes used in the template to apply correctly
5. MJML may import and apply the Ubuntu font if you don't explicitly state the font-family in a text field: if you don't want this font, you may remove the import and replace it in the font-family attributes
6. restore custom developments as well: they are flagged with <!-- GoFAST --> and /** GoFAST */ comments in the original .tpl.php file