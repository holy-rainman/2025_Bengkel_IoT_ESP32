[
    {
        "id": "3cbda349bd186fa5",
        "type": "tab",
        "label": "LED Control 8-bit",
        "disabled": false,
        "info": "",
        "env": []
    },
    {
        "id": "e2e4de6d6e13d5f5",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 1",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 3,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led1_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led1_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 380,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "da8c7f11821aa405",
        "type": "mqtt out",
        "z": "3cbda349bd186fa5",
        "name": "",
        "topic": "/LedControl",
        "qos": "",
        "retain": "",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "acd8922375aaedc6",
        "x": 1150,
        "y": 460,
        "wires": []
    },
    {
        "id": "a503fdc2d5d14406",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 2",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 4,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led2_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led2_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 440,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "1f98b2264e59015d",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 3",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 5,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led3_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led3_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 500,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "7add64a3da19bc39",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 4",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 6,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led4_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led4_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 560,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "6d5025f90c639633",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 5",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 7,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led5_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led5_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 620,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "baa9a1b28ee82c53",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 6",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 8,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led6_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led6_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 680,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "89b30ecab9215a83",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 7",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 9,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led7_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led7_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 740,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "8be89c7e06fea615",
        "type": "ui_switch",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED 8",
        "tooltip": "",
        "group": "7a8ea489af191eb8",
        "order": 10,
        "width": 0,
        "height": 0,
        "passthru": false,
        "decouple": "true",
        "topic": "/LedControl",
        "topicType": "msg",
        "style": "",
        "onvalue": "led8_1",
        "onvalueType": "str",
        "onicon": "",
        "oncolor": "",
        "offvalue": "led8_0",
        "offvalueType": "str",
        "officon": "",
        "offcolor": "",
        "animate": false,
        "className": "",
        "x": 710,
        "y": 800,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "1bb816a83d6fbf39",
        "type": "ui_button",
        "z": "3cbda349bd186fa5",
        "name": "",
        "group": "7a8ea489af191eb8",
        "order": 2,
        "width": 0,
        "height": 0,
        "passthru": false,
        "label": "All OFF",
        "tooltip": "",
        "color": "",
        "bgcolor": "",
        "className": "",
        "icon": "",
        "payload": "all_off",
        "payloadType": "str",
        "topic": "/LedControl",
        "topicType": "msg",
        "x": 720,
        "y": 320,
        "wires": [
            [
                "6eaaefe6bf9f2559",
                "d4e202b9ad8216e4"
            ]
        ]
    },
    {
        "id": "6eaaefe6bf9f2559",
        "type": "function",
        "z": "3cbda349bd186fa5",
        "name": "All OFF",
        "func": "let messages = [];\n\nfor (let i = 1; i <= 8; i++) {\n    messages.push({ topic: \"/LedControl\", payload: \"led\" + i + \"_0\" });\n}\n\nreturn [messages];",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 880,
        "y": 320,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "6d876982b81f86cf",
        "type": "mqtt in",
        "z": "3cbda349bd186fa5",
        "name": "",
        "topic": "/LedControl",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "acd8922375aaedc6",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 470,
        "y": 480,
        "wires": [
            [
                "e2e4de6d6e13d5f5",
                "a503fdc2d5d14406",
                "1f98b2264e59015d",
                "7add64a3da19bc39",
                "6d5025f90c639633",
                "baa9a1b28ee82c53",
                "89b30ecab9215a83",
                "8be89c7e06fea615",
                "5b98519f4699bd36"
            ]
        ]
    },
    {
        "id": "1e027c98f3ff37d1",
        "type": "mqtt in",
        "z": "3cbda349bd186fa5",
        "name": "",
        "topic": "/Button1Status",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "acd8922375aaedc6",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 460,
        "y": 920,
        "wires": [
            [
                "d3069dafea359b50"
            ]
        ]
    },
    {
        "id": "d3069dafea359b50",
        "type": "ui_text",
        "z": "3cbda349bd186fa5",
        "group": "13f09cef26df5309",
        "order": 1,
        "width": 0,
        "height": 0,
        "name": "",
        "label": "PB1",
        "format": "{{msg.payload}}",
        "layout": "row-spread",
        "className": "",
        "style": false,
        "font": "",
        "fontSize": 16,
        "color": "#000000",
        "x": 710,
        "y": 920,
        "wires": []
    },
    {
        "id": "8bd22e64a888c48b",
        "type": "mqtt in",
        "z": "3cbda349bd186fa5",
        "name": "",
        "topic": "/Button2Status",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "acd8922375aaedc6",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 460,
        "y": 980,
        "wires": [
            [
                "ab44e94a9651f11c"
            ]
        ]
    },
    {
        "id": "ab44e94a9651f11c",
        "type": "ui_text",
        "z": "3cbda349bd186fa5",
        "group": "13f09cef26df5309",
        "order": 2,
        "width": 0,
        "height": 0,
        "name": "",
        "label": "PB2",
        "format": "{{msg.payload}}",
        "layout": "row-spread",
        "className": "",
        "style": false,
        "font": "",
        "fontSize": 16,
        "color": "#000000",
        "x": 710,
        "y": 980,
        "wires": []
    },
    {
        "id": "11532a174f59e2d8",
        "type": "ui_button",
        "z": "3cbda349bd186fa5",
        "name": "",
        "group": "7a8ea489af191eb8",
        "order": 1,
        "width": 0,
        "height": 0,
        "passthru": false,
        "label": "All ON",
        "tooltip": "",
        "color": "",
        "bgcolor": "",
        "className": "",
        "icon": "",
        "payload": "all_on",
        "payloadType": "str",
        "topic": "/LedControl",
        "topicType": "msg",
        "x": 710,
        "y": 240,
        "wires": [
            [
                "cd54592169def958",
                "b4dc205066ab89a0"
            ]
        ]
    },
    {
        "id": "cd54592169def958",
        "type": "function",
        "z": "3cbda349bd186fa5",
        "name": "All ON",
        "func": "let messages = [];\n\nfor (let i = 1; i <= 8; i++) {\n    messages.push({ topic: \"/LedControl\", payload: \"led\" + i + \"_1\" });\n}\n\nreturn [messages];",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 870,
        "y": 240,
        "wires": [
            [
                "da8c7f11821aa405"
            ]
        ]
    },
    {
        "id": "5b98519f4699bd36",
        "type": "ui_slider",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED Slider",
        "tooltip": "",
        "group": "2c7361bb3cce86c5",
        "order": 1,
        "width": 0,
        "height": 0,
        "passthru": false,
        "outs": "all",
        "topic": "/SliderControl",
        "topicType": "msg",
        "min": 0,
        "max": "8",
        "step": 1,
        "className": "",
        "x": 470,
        "y": 1060,
        "wires": [
            [
                "9f08a82b84d1ebcb",
                "d3810887216b5810"
            ]
        ]
    },
    {
        "id": "9f08a82b84d1ebcb",
        "type": "mqtt out",
        "z": "3cbda349bd186fa5",
        "name": "",
        "topic": "/SliderControl",
        "qos": "",
        "retain": "",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "acd8922375aaedc6",
        "x": 740,
        "y": 1060,
        "wires": []
    },
    {
        "id": "39ddaedd90ccf811",
        "type": "ui_text",
        "z": "3cbda349bd186fa5",
        "group": "2c7361bb3cce86c5",
        "order": 2,
        "width": 0,
        "height": 0,
        "name": "",
        "label": "Slider status",
        "format": "{{msg.payload}}",
        "layout": "row-spread",
        "className": "",
        "style": false,
        "font": "",
        "fontSize": 16,
        "color": "#000000",
        "x": 930,
        "y": 1120,
        "wires": []
    },
    {
        "id": "f0d5c72689acd453",
        "type": "ui_dropdown",
        "z": "3cbda349bd186fa5",
        "name": "",
        "label": "LED Selection",
        "tooltip": "Choose which LED to turn ON for 2 seconds",
        "place": "Select option",
        "group": "2c7361bb3cce86c5",
        "order": 4,
        "width": 0,
        "height": 0,
        "passthru": true,
        "multiple": false,
        "options": [
            {
                "label": "LED1",
                "value": "LED1",
                "type": "str"
            },
            {
                "label": "LED2",
                "value": "LED2",
                "type": "str"
            },
            {
                "label": "LED3",
                "value": "LED3",
                "type": "str"
            },
            {
                "label": "LED4",
                "value": "LED4",
                "type": "str"
            },
            {
                "label": "LED5",
                "value": "LED5",
                "type": "str"
            },
            {
                "label": "LED6",
                "value": "LED6",
                "type": "str"
            },
            {
                "label": "LED7",
                "value": "LED7",
                "type": "str"
            },
            {
                "label": "LED8",
                "value": "LED8",
                "type": "str"
            }
        ],
        "payload": "",
        "topic": "/MenuControl",
        "topicType": "msg",
        "className": "",
        "x": 480,
        "y": 1200,
        "wires": [
            [
                "f86b5f5e28853a9b",
                "2bf7d1aeb84dd315"
            ]
        ]
    },
    {
        "id": "f86b5f5e28853a9b",
        "type": "mqtt out",
        "z": "3cbda349bd186fa5",
        "name": "",
        "topic": "/MenuControl",
        "qos": "",
        "retain": "",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "acd8922375aaedc6",
        "x": 800,
        "y": 1200,
        "wires": []
    },
    {
        "id": "2bf7d1aeb84dd315",
        "type": "delay",
        "z": "3cbda349bd186fa5",
        "name": "",
        "pauseType": "delay",
        "timeout": "2",
        "timeoutUnits": "seconds",
        "rate": "1",
        "nbRateUnits": "1",
        "rateUnits": "second",
        "randomFirst": "1",
        "randomLast": "5",
        "randomUnits": "seconds",
        "drop": false,
        "allowrate": false,
        "outputs": 1,
        "x": 780,
        "y": 1300,
        "wires": [
            [
                "c08f151742406924"
            ]
        ]
    },
    {
        "id": "c08f151742406924",
        "type": "function",
        "z": "3cbda349bd186fa5",
        "name": "Reset Dropdown",
        "func": "return {\n    payload: \n    {   value: 0 \n    }\n};",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 970,
        "y": 1300,
        "wires": [
            [
                "f0d5c72689acd453"
            ]
        ]
    },
    {
        "id": "d4e202b9ad8216e4",
        "type": "function",
        "z": "3cbda349bd186fa5",
        "name": "Reset Slider",
        "func": "let messages = [];\nmessages.push({ topic: \"/SliderControl\", payload: \"0\" });\n\nreturn [messages];",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 890,
        "y": 360,
        "wires": [
            [
                "da8c7f11821aa405",
                "39ddaedd90ccf811"
            ]
        ]
    },
    {
        "id": "b4dc205066ab89a0",
        "type": "function",
        "z": "3cbda349bd186fa5",
        "name": "Set Slider",
        "func": "let messages = [];\nmessages.push({ topic: \"/SliderControl\", payload: \"8\" });\n\nreturn [messages];",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 880,
        "y": 280,
        "wires": [
            [
                "da8c7f11821aa405",
                "39ddaedd90ccf811"
            ]
        ]
    },
    {
        "id": "d3810887216b5810",
        "type": "function",
        "z": "3cbda349bd186fa5",
        "name": "Reset slider if PB ALL OFF",
        "func": "\nreturn msg;",
        "outputs": 1,
        "timeout": 0,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 700,
        "y": 1120,
        "wires": [
            [
                "39ddaedd90ccf811"
            ]
        ]
    },
    {
        "id": "d3be592a7b49a775",
        "type": "ui_spacer",
        "z": "3cbda349bd186fa5",
        "name": "spacer",
        "group": "2c7361bb3cce86c5",
        "order": 3,
        "width": 1,
        "height": 1
    },
    {
        "id": "7a8ea489af191eb8",
        "type": "ui_group",
        "name": "LED Control 8-bit",
        "tab": "851f28bf5102a4c1",
        "order": 1,
        "disp": true,
        "width": 6,
        "collapse": false,
        "className": ""
    },
    {
        "id": "acd8922375aaedc6",
        "type": "mqtt-broker",
        "name": "broker.emqx.io",
        "broker": "broker.emqx.io",
        "port": 1883,
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": 4,
        "keepalive": 60,
        "cleansession": true,
        "autoUnsubscribe": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthRetain": "false",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closeQos": "0",
        "closeRetain": "false",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willRetain": "false",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    },
    {
        "id": "13f09cef26df5309",
        "type": "ui_group",
        "name": "Push Button Status",
        "tab": "851f28bf5102a4c1",
        "order": 2,
        "disp": true,
        "width": "5",
        "collapse": false,
        "className": ""
    },
    {
        "id": "2c7361bb3cce86c5",
        "type": "ui_group",
        "name": "LED Control Option",
        "tab": "851f28bf5102a4c1",
        "order": 3,
        "disp": true,
        "width": 6,
        "collapse": false,
        "className": ""
    },
    {
        "id": "851f28bf5102a4c1",
        "type": "ui_tab",
        "name": "LED",
        "icon": "dashboard",
        "order": 2,
        "disabled": false,
        "hidden": false
    }
]
