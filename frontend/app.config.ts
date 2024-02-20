export default defineAppConfig({
    title: 'Hello Nuxt',
    theme: {
      dark: true,
      colorsLight: {
        primaryColor_: '#19CC30',
        primaryAccentColor_: '#10DD60',
        secondaryColor_: '#1299FF',
        backgroundColor_: '#EEE',
        backgroundSecondaryColor_: '#AAA',
        borderBoxColor: '#666',
        textPrimaryColor: '#222',
        textSecondaryColor: '#888',
        textLinkColor: '#10DD60'
      },
      colorsDark: {
        primaryColor_: '#0092BA',
        primaryAccentColor_: '#00D4A2',
        secondaryColor_: '#C23373',
        backgroundColor_: '#222',
        backgroundSecondaryColor_: '#333',
        borderBoxColor: '#666',
        textPrimaryColor: '#ddd',
        textSecondaryColor: '#aaa',
        textLinkColor: '#C23373'
      },
      typography: {
        fontSize : {
          xs: '14px',
          sm: '16px',
          md: '20px',
          lg: '28px',
          xl: '32px',
          xxl: '38px'
        },
        letterSpacing: '-1px'
      },
      border: {
        borderRadius_: '6px',
        borderBoxes_: '2px solid',
      },
      padding: {
        paddingButtonX: '20px',
        paddingButtonY: '10px',
        paddingBoxesX: '10px',
        paddingBoxesY: '10px',
      }
    }
  })