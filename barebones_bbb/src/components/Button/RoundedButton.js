import React from 'react'
import RaisedButton from 'material-ui/RaisedButton'
import Radium from 'radium'

const styles = {
  borderRadius: 50,
}

const RoundedButton = props => (
  <RaisedButton
    disableTouchRipple
    buttonStyle={styles}
    style={styles}
    overlayStyle={styles}
    {...props}
  />
)

export default Radium(RoundedButton)
